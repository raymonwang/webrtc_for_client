/*
*
*
*  Copyright by ztgame@2017
*  Written by lfz 
*
*
*/

#include "rtc_fec.h"


static const uint8_t kSecPT = 0x4d;
static const uint32_t kMaxFecPacketNum = 512;   // must be 2^n

RtcFecEncoder::~RtcFecEncoder()
{
	if (session) {
		of_release_codec_instance(session);
		session = nullptr;
	}
		
	free_list.clear();
	packet_list.clear();
}

RtcFecEncoder* RtcFecEncoder::Create(const uint32_t source_num,
									 const uint32_t repair_num,
									 const uint32_t max_length,
									 RtcFecEncoderCallback *callback)
{
	RtcFecEncoder *fec_enc = new RtcFecEncoder(callback);
	if (0 == fec_enc->Init(source_num, repair_num, max_length))
		return fec_enc;

	LOG(LS_WARNING) << "Create fec encoder failed";
	delete fec_enc;
	return nullptr;
}

int RtcFecEncoder::Init(const uint32_t source_num, const uint32_t repair_num,
						const uint32_t max_length)
{
	param.nb_source_symbols = source_num;
	param.nb_repair_symbols = repair_num;
	param.encoding_symbol_length = max_length + sizeof(int);
	param.m = 8;
	if (0 != CreateFecInstance())
		return -1;
	
	// start sequence number must be a multiple of Rows()
	start_seq = current_seq = kMaxFecPacketNum * 77;
	return 0;
}

bool RtcFecEncoder::OnReceiveReport(const uint32_t ssrc, const uint32_t cumulative_lost, 
									const uint16_t highest_seq_num)
{
	LossStatics *loss = nullptr;
	auto it = recv_reports.find(ssrc);
	if (it == recv_reports.end()) {
		std::unique_ptr<LossStatics> loss_statics(new LossStatics());
		loss = loss_statics.get();
		recv_reports[ssrc] = std::move(loss_statics);
	} else {
		loss = it->second.get();
	}

	loss->highest_seq_ = highest_seq_num;	
	loss->repair_need = std::max((cumulative_lost - loss->cumulative_lost_), loss->repair_need);
	loss->cumulative_lost_ = cumulative_lost;
	if (loss->repair_need)
		loss->last_zero_loss_time = rtc::TimeMillis();
	
	return 0 < loss->repair_need;
}

bool RtcFecEncoder::InsertPacket(const uint8_t *data, const uint32_t size)
{	
	Buffer *packet = GetPacket();	
	if (!packet) {
		LOG(LS_ERROR) << "get packet for source packet failed";
		return false;
	}

	WriteFecSourcePacket(packet, data, size);
	packet_list.push_back(packet);
	if (param.nb_source_symbols > packet_list.size())
		return false;

	uint32_t ssrc = rtc::GetBE32(data + 8);
	uint32_t timestamp = rtc::GetBE32(data + 4);
	SendFecRepairPacket(ssrc, (timestamp > 100 ? (timestamp - 100) : 0));
	start_seq = current_seq;
	RecyclePacket();

	UpdateFecRepair();
	return true;
}

void RtcFecEncoder::UpdateFecRepair()
{
	uint32_t old_repair_symbols = param.nb_repair_symbols;
	uint32_t repair_add = 0;
	int64_t  last_zero_loss_time = 0;
	for (const auto& it : recv_reports) {
		repair_add = std::max(it.second->repair_need, repair_add);
		it.second->repair_need = 0;
	
		last_zero_loss_time = std::max(it.second->last_zero_loss_time, last_zero_loss_time);	
	}

	param.nb_repair_symbols += repair_add;
	param.nb_repair_symbols = std::min(param.nb_source_symbols, param.nb_repair_symbols);

	int64_t now = rtc::TimeMillis();
	if (!repair_add && last_zero_loss_time && ((last_zero_loss_time + 30000) < now)) {
		param.nb_repair_symbols -= 1 < param.nb_repair_symbols ? 1 : 0;

		for (const auto& it : recv_reports)
			it.second->last_zero_loss_time = now;		
	}

	if (old_repair_symbols != param.nb_repair_symbols) {
		LOG(LS_WARNING) << "modify fec param to [" << param.nb_source_symbols << ", "
						<< param.nb_repair_symbols << "]";
		if (session)
			of_release_codec_instance(session);
		CreateFecInstance();
	}	
}

Buffer* RtcFecEncoder::GetPacket()
{
	if (!free_list.empty()) {
		Buffer *buffer = free_list.front();
		free_list.pop_front();
		return buffer;
	}

	return new Buffer(0, MaxSize());
}

void RtcFecEncoder::WriteFecSourcePacket(Buffer *packet, 
										const uint8_t *data, const uint32_t size)
{
	uint8_t *buffer = packet->data();
	uint32_t ssrc = rtc::GetBE32(data + 8);
	uint32_t timestamp = rtc::GetBE32(data + 4);
	InitFecHeader(buffer, ssrc, timestamp);
	uint32_t len = sizeof(FecHeader);

	// set payload length
	buffer[len++] = last_encoded_timestamp != timestamp;
	buffer[len++] = data[1] & 0x80 ? 1 : 0;
	rtc::SetBE16(buffer + len, (uint16_t)size);
	len += sizeof(uint16_t);

	// set payload value
	memcpy(buffer + len, data, size);
	len += size;
	if (MaxSize() > len)
		memset(buffer + len, 0x0, MaxSize() - len);

	packet->SetSize(len);
	last_encoded_timestamp = timestamp;
	callback_ ? callback_->SendPacket(buffer, len) : 0;	
}

int RtcFecEncoder::SendFecRepairPacket(const uint32_t ssrc, const uint32_t timestamp)
{
	uint32_t rows = param.nb_source_symbols + param.nb_repair_symbols;
	uint32_t columns = param.nb_source_symbols;

	std::unique_ptr<uint8_t> ptr(new uint8_t[rows * sizeof(void*)]);
	void **packet_pointer = (void**)(ptr.get());
	
	size_t max_payload_size = 0;
	for (uint32_t i = 0; i < columns; i++) {
		packet_pointer[i] = packet_list[i]->data() + sizeof(FecHeader);
		max_payload_size = std::max(max_payload_size, packet_list[i]->size());
	}
		
	for (uint32_t i = columns; i < rows; i++) {
		Buffer *packet = GetPacket();
		if (!packet) {
			LOG(LS_ERROR) << "get packet for repair failed";
			return -1;
		}

		InitFecHeader(packet->data(), ssrc, timestamp);
		packet_pointer[i] = packet->data() + sizeof(FecHeader);
		of_build_repair_symbol(session, packet_pointer, i);
		callback_ ? callback_->SendPacket(packet->data(), max_payload_size) : 0;
		packet_list.push_back(packet);
	}

	return 0;
}

void RtcFecEncoder::InitFecHeader(uint8_t *buffer, const uint32_t ssrc, const uint32_t timestamp)
{
	// fec header is like rtp header, so when received fec packet, remote can see
	// who send this packet by ssrc
	FecHeader *header =(FecHeader*)buffer;
	header->version = 0x80;
	header->pt = kSecPT;

	rtc::SetBE16(&header->seq_num, current_seq++);
	if (current_seq == (UINT16_MAX - (UINT16_MAX % kMaxFecPacketNum)))
		current_seq = 0;
	
	// reserved for fec encoder info: source num, repair num, max length
	rtc::SetBE32(&header->info, timestamp);
	rtc::SetBE32(&header->ssrc, ssrc);
	header->sources = param.nb_source_symbols;
	header->repairs = param.nb_repair_symbols;
	rtc::SetBE16(&header->start_seq, start_seq);
}

void RtcFecEncoder::RecyclePacket()
{
	auto it = packet_list.begin();
	while (it != packet_list.end()) {
		free_list.push_back(*it);
		it = packet_list.erase(it);
	}

	packet_list.clear();
}

int RtcFecEncoder::CreateFecInstance()
{	
	const of_codec_id_t codec_id = OF_CODEC_REED_SOLOMON_GF_2_M_STABLE;
	if (0 == of_create_codec_instance(&session, codec_id, OF_ENCODER, 2) && 
		0 == of_set_fec_parameters(session, (of_parameters_t*)&param))
		return 0;

	return -1;	
}

RtcFecDecoder::~RtcFecDecoder()
{
	if (worker)
		worker->Stop();
	
	if (session) {
		of_release_codec_instance(session);
		session = nullptr;
	}

	if (fec_pointer) {
		delete[] fec_pointer;
		fec_pointer = nullptr;
	}

	if (raw_pointer) {
		delete[] raw_pointer;
		raw_pointer = nullptr;
	}
		
	packet_list.clear();
}

RtcFecDecoder* RtcFecDecoder::Create(const uint32_t source_num,
									 const uint32_t repair_num,
									 const uint32_t max_length,
									 RtcFecDecoderCallback *callback)
{
	RtcFecDecoder *fec_dec = new RtcFecDecoder(callback);
	if (0 == fec_dec->Init(source_num, repair_num, max_length))
		return fec_dec;

	LOG(LS_WARNING) << "Create fec decoder failed";
	delete fec_dec;
	return nullptr;
}

int RtcFecDecoder::Init(const uint32_t source_num, const uint32_t repair_num,
						const uint32_t max_length)
{
	LOG(LS_WARNING) << "Init fec decoder: source " << source_num
					<< " repair " << repair_num << " max length " << max_length;
	param_.nb_source_symbols = source_num;
	param_.nb_repair_symbols = repair_num;
	param_.encoding_symbol_length = max_length + sizeof(int);
	param_.m = 8;

	const uint32_t kMaxRows = 24;
	fec_pointer = (uint8_t**)(new uint8_t[kMaxRows* sizeof(uint8_t*)]);
	raw_pointer = (uint8_t**)(new uint8_t[kMaxRows * sizeof(uint8_t*)]);
	for (uint32_t i = 0; i < kMaxRows; i++)
		fec_pointer[i] = raw_pointer[i] = nullptr;

	for (uint32_t i = 0; i < kMaxFecPacketNum; i++) 		
		packet_list.emplace_back(new FecPacket());

	worker->Start();
	return 0;
}

int RtcFecDecoder::InsertFecData(const uint8_t *data, const uint32_t size)
{
	if (kSecPT != (data[1] & 0x7f))
		return callback_->ReceivePacket(data, size);

	if (MaxSize() < size || MinSize() >= size) {
		LOG(LS_WARNING) << "Insert fec data, size " << size << " is invalid";
		return -1;
	}

	uint16_t seq = rtc::GetBE16(data + 2);
	uint16_t start_seq = rtc::GetBE16(data + 14);
	uint32_t index = seq % packet_list.size();
	uint32_t timestamp = rtc::GetBE32(data + 4);

	CritScope cs(lock.get());
	LOG(LS_INFO) << "insert packet: seq " << seq << " start seq " << start_seq
				 << " timestamp " << timestamp << " last timestamp " << last_decoded_timestamp
				 << " last start seq " << last_start_seq_;
	
	if (timestamp < last_decoded_timestamp && start_seq == last_start_seq_)
		return 0;
	
	FecPacket *packet = packet_list[index].get();
	if (packet->status) {
		LOG(LS_WARNING) << "new packet " << seq << " is coming, flush old buffer"
						<< " index " << index << " status is " << packet->status;
//		DecodedLastPacket(index);
		FreeFecSequence((FecHeader*)data);
	}

	if (NeedToInsert((FecHeader*)data)) {
		WriteFecData(index, data, size);
//		last_insert_timestamp = std::max(last_insert_timestamp, timestamp);

		// received k packet OR received end packet of one frame
		if (NeedSetEvent((FecHeader*)data))
			event_->Set();
	} 

	return 0;
}

void RtcFecDecoder::FreeFecSequence(const FecHeader *header)
{
	uint16_t start_seq = rtc::GetBE16(&header->start_seq);
	uint32_t start_idx = start_seq % packet_list.size();
	uint32_t rows = header->sources + header->repairs;
	for (uint32_t i = 0; i < rows; i++) {
		uint32_t index = (start_idx + i) & (packet_list.size() - 1);
		FecPacket *packet = packet_list[index].get();
		if (packet->status & kInserted && packet->start_seq != start_seq) {
			LOG(LS_WARNING) << "modify index " << index << " status " << packet->status
							<< " for start seq " << packet->start_seq << " is not equal with "
							<< start_seq;
			packet->status = 0;
		}			
	}
}

bool RtcFecDecoder::NeedToInsert(const FecHeader *header)
{
	uint16_t start_seq = rtc::GetBE16(&header->start_seq);
	uint16_t now_seq   = rtc::GetBE16(&header->seq_num);
	if (now_seq < (start_seq + header->sources))
		return true;

	uint32_t start_idx = start_seq % packet_list.size();
	uint32_t received_num = 0;
	uint32_t rows = header->sources + header->repairs;
	for (uint32_t i = 0; i < rows; i++) {
		uint32_t index = (start_idx + i) & (packet_list.size() - 1);
//		index -= packet_list.size() <= index ? packet_list.size() : 0;
		received_num += packet_list[index]->status & kInserted;
	}
		
	return header->sources > received_num;
}

bool RtcFecDecoder::NeedSetEvent(const FecHeader *header)
{
	uint32_t index = rtc::GetBE16(&header->seq_num) % packet_list.size();
	FecPacket *packet = packet_list[index].get();
	if (packet->source && packet->frame_end)
		return true;

	uint32_t start_idx = rtc::GetBE16(&header->start_seq) % packet_list.size();
	uint32_t received_num = 0;
	uint32_t rows = header->sources + header->repairs;
	for (uint32_t i = 0; i < rows; i++) {
		index = (start_idx + i) & (packet_list.size() - 1);
//		index -= index >= packet_list.size() ? packet_list.size() : 0;
		received_num += packet_list[index]->status & kInserted;
	}

	return header->sources <= received_num;
}

void RtcFecDecoder::WriteFecData(const uint32_t index, const uint8_t *data, const uint32_t size)
{
	FecHeader *header = (FecHeader*)data;		
	FecPacket *packet = packet_list[index].get();
	memcpy(packet->data, data, size);
	if (MaxSize() > size)
		memset(packet->data + size, 0x0, MaxSize() - size);
	packet->size = size;
	
	packet->status = kInserted;
	packet->start_seq = rtc::GetBE16(&header->start_seq);
	packet->source_num = header->sources;
	packet->repair_num = header->repairs;
	packet->source = (packet->start_seq + packet->source_num) > rtc::GetBE16(&header->seq_num);
	packet->frame_begin = packet->source ? data[sizeof(FecHeader)] : false;
	packet->frame_end = packet->source ? data[sizeof(FecHeader) + 1] : true;
	packet->timestamp = packet->source ? rtc::GetBE32(data + MinSize() + 4) : 0;

	LOG(LS_INFO) << "insert " << (packet->source ? "SS" : "RR") << ", index " 
				 << index << " seq " << rtc::GetBE16(data + 2) << " start " << packet->start_seq 
				 << " source " << packet->source_num << " repair " << packet->repair_num
				 << " timestamp " << packet->timestamp << " frame [" << packet->frame_begin
				 << " " << packet->frame_end << "]" << " arrived " << rtc::TimeMillis();

}

bool RtcFecDecoder::Runnable(void *obj)
{
	static_cast<RtcFecDecoder*>(obj)->Process();
	return true;
}

void RtcFecDecoder::Process()
{
	event_->Wait(100);
	CritScope cs(lock.get());
	DecodedFec();
	DeliverFrame();
}

int RtcFecDecoder::DecodedFec()
{
	uint32_t start_idx = next_decoded_idx_;
	uint32_t loop = 0;
	while (packet_list.size() > loop) {
		uint32_t rows = FindNextSequence(start_idx);
		if (packet_list.size() <= rows || 0 == rows)
			break;

		if (DecodedPacket(start_idx, rows)) 
			break;

		loop += rows;
		start_idx = (start_idx + rows) & (packet_list.size() - 1);
//		start_idx += rows;
//		start_idx -= packet_list.size() <= start_idx ? packet_list.size() : 0;
	}

	return 0;
}

uint32_t RtcFecDecoder::FindNextSequence(const uint32_t index)
{
	uint32_t loop = 0;
	while (packet_list.size() > loop) {
		uint32_t start_idx = (index + (loop++)) & (packet_list.size() - 1);
//		start_idx -= packet_list.size() <= start_idx ? packet_list.size() : 0;
		FecPacket *packet = packet_list[start_idx].get();
		if (!(packet->status & kInserted))
			continue;

		start_idx = packet->start_seq % packet_list.size();
		if (index == start_idx)
			return packet->source_num + packet->repair_num;

		return index < start_idx ? (start_idx - index) : (start_idx + packet_list.size() - index);
	}

	return packet_list.size();
}

#if 0
void RtcFecDecoder::DecodedLastPacket(const uint32_t index)
{
	uint32_t start_idx = index - index % Rows();

	for (size_t i = 0; i < Rows(); i++) {
		FecPacket *packet = packet_list[start_idx + i].get();
		if (!(packet->status & kInserted))
			continue;

		if (packet->status & kDecoded)
			break;

		if (packet->status & kDelivered)
			packet->status = 0;
	}
}
#endif

bool RtcFecDecoder::DecodedPacket(const uint32_t index, const uint32_t rows)
{
	uint32_t columns = 0;
	uint32_t start_seq = 0;
	uint32_t received_num = 0;
	bool all_source_received = true;
	for (size_t i = 0; i < rows; i++) {
		uint32_t start_index = (index + i) & (packet_list.size() - 1);
//		start_index -= packet_list.size() <= start_index ? packet_list.size() : 0;
		FecPacket *packet = packet_list[start_index].get();
		if (packet->status & kDecoded) {
			received_num = 0;
			break;
		}

		if (packet->status & kInserted) {
			if (0 == received_num) {
				columns = packet->source_num;
				start_seq = packet->start_seq;
			}

			received_num += (columns == packet->source_num && start_seq == packet->start_seq);		
		} else {
			all_source_received = (!columns || i < columns) ? false : all_source_received;
		}
	}

	if (received_num && columns <= received_num) {
		all_source_received ? 0 : Decoded(index, rows, columns);
		ResetDecoder(index, rows, columns);
		last_start_seq_ = start_seq;
		LOG(LS_INFO) << "Decoded fec: start index " << index << " received " << received_num 
					 << " start seq " << last_start_seq_ 
					 << " next decoded index " << next_decoded_idx_;
		return true;
	}

	return false;
}

int RtcFecDecoder::Decoded(const uint32_t index, const uint32_t rows, const uint32_t columns)
{
	for (size_t i = 0; i < rows; i++) {
		uint32_t start_idx = (index + i) & (packet_list.size() -  1);
		FecPacket *packet = packet_list[start_idx].get();
		fec_pointer[i] = (packet->status & kInserted) ? (packet->data + sizeof(FecHeader)) : nullptr;
	}

	if (0 != CreateFecInstance(rows, columns)) {
		LOG(LS_ERROR) << "create fec instance failed";
		return -1;
	}

	if (0 != of_set_available_symbols(session, (void**)fec_pointer)) {
		LOG(LS_ERROR) << "fec set available symbols failed";
		return -1;
	}

	if (0 != of_finish_decoding(session)) {
		LOG(LS_ERROR) << "fec finish decoding failed";
		return -1;
	}

	if (0 != of_get_source_symbols_tab(session, (void**)raw_pointer)) {
		LOG(LS_ERROR) << "fec get source symbols failed";
		return -1;
	}

	for (size_t i = 0; i < columns; i++) {
		if (raw_pointer[i] && !fec_pointer[i]) {
			uint32_t start_idx = (index + i) & (packet_list.size() - 1);
			FecPacket *packet = packet_list[start_idx].get();
			packet->status = kInserted;
			packet->source = true;
			packet->frame_begin = raw_pointer[i][0];
			packet->frame_end   = raw_pointer[i][1];
			packet->timestamp   = rtc::GetBE32(raw_pointer[i] + 8);
			
			uint32_t size = rtc::GetBE16(raw_pointer[i] + 2);
			memcpy(packet->data + sizeof(FecHeader), raw_pointer[i], size + sizeof(uint32_t));
			packet->size = MinSize() + size;
			free(raw_pointer[i]);
		}
	}

	return 0;
}

int RtcFecDecoder::ResetDecoder(const uint32_t index, const uint32_t rows, const uint32_t columns)
{
	if (session) {
		of_release_codec_instance(session);
		session = nullptr;
	}

	uint32_t timestamp = 0;
	for (size_t i = 0; i < rows; i++) {
		fec_pointer[i] = nullptr;
		raw_pointer[i] = nullptr;

		uint32_t current_idx = (index + i) & (packet_list.size() - 1);
//		current_idx -= packet_list.size() <= current_idx ? packet_list.size() : 0;
		FecPacket *packet = packet_list[current_idx].get();
		if (columns <= i) {
			packet->status = kInserted | kDecoded;
			packet->source = false;
		} else {
			timestamp = std::max(timestamp, packet->timestamp);
			packet->status |= kDecoded;
			if (kReleased == packet->status)
				packet->status = 0;			
		}
	}

	last_decoded_timestamp = std::max(last_decoded_timestamp, timestamp);
	next_decoded_idx_ = (index + rows) & (packet_list.size() - 1);
	return 0;
}

void RtcFecDecoder::DeliverFrame()
{
	if (packet_list.size() <= last_frame_idx) {
		LOG(LS_ERROR) << "last complete frame index " << last_frame_idx << " is invalid";
		return;
	}

	uint32_t loop = 0;
	while (packet_list.size() > loop) {
		FecPacket *packet = packet_list[last_frame_idx].get();
		if ((packet->status & kInserted) && !packet->source) {
			loop++;
			last_frame_idx = (last_frame_idx + 1) & (packet_list.size() - 1);
//			last_frame_idx -= packet_list.size() <= last_frame_idx ? packet_list.size() : 0;
			packet->status = 0;
			continue;
		}

		uint32_t end_idx = GetCompleteFrame(last_frame_idx);
		// not complete frame
		if (packet_list.size() <= end_idx) {
			ResetNotCompleteFrame(last_frame_idx);
			break;
		}

		uint32_t packet_num = DeliverPacket(last_frame_idx, end_idx);
		loop += packet_num;
		last_frame_idx += packet_num;
		last_frame_idx &= (packet_list.size() - 1);
//		last_frame_idx -= packet_list.size() <= last_frame_idx ? packet_list.size() : 0;

//		if (packet_list[end_idx]->timestamp == last_insert_timestamp)
//			break;
	}
}

uint32_t RtcFecDecoder::DeliverPacket(const uint32_t start_idx, const uint32_t end_idx)
{
	uint32_t packet_num = end_idx >= start_idx ? (end_idx - start_idx) 
											   : (end_idx + packet_list.size() - start_idx);
	packet_num++;

	uint32_t loop = 0;
	while (packet_num > loop) {
		uint32_t index = (start_idx + (loop++)) & (packet_list.size() - 1);
//		index -= index >= packet_list.size() ? packet_list.size() : 0;
		FecPacket *packet = packet_list[index].get();
		if (!(packet->status & kInserted))
			continue;

		packet->status |= kDelivered;
		if (kReleased == packet->status)
			packet->status = 0;
		
		if (packet->source && MaxSize() >= packet->size)
			callback_->ReceivePacket(packet->data + MinSize(), packet->size - MinSize());
	}

	LOG(LS_INFO) << "deliver packet: start index " << start_idx << " end index " << end_idx
				 << " packet num " << packet_num;
	return packet_num;
}

uint32_t RtcFecDecoder::GetCompleteFrame(const uint32_t index)
{
	uint32_t end_idx = index;
	uint32_t timestamp = 0;

	uint32_t loop = 0;
	while (packet_list.size() > loop) {
		++loop;

		FecPacket *packet = packet_list[end_idx].get();
		// have loss packet
		if (!(packet->status & kInserted))
			break;
		
		// skip repair packet
		if (!packet->source) {
			end_idx = (end_idx + 1) & (packet_list.size() - 1);
//			end_idx = (++end_idx >= packet_list.size()) ? 0 : end_idx;
			continue;
		}
			
		if (packet->frame_begin)
			timestamp = packet->timestamp;

		if (timestamp != packet->timestamp) {
			LOG(LS_ERROR) << "get frame: index " << end_idx << " timestamp " << packet->timestamp
						  << " is not equal with " << timestamp;
			break;
		}
		
		// seek to frame end packet
		if (packet->frame_end) 
			return end_idx;

		end_idx = (end_idx + 1) & (packet_list.size() - 1);
//		end_idx = (++end_idx >= packet_list.size()) ? 0 : end_idx;
	}

	return packet_list.size();
}

void RtcFecDecoder::ResetNotCompleteFrame(const uint32_t index)
{
	uint32_t next_frame_idx = packet_list.size();
	uint32_t timestamp = 0;
	uint32_t loop = 0;
	while (packet_list.size() > loop) {
		uint32_t start_idx = (index + (++loop)) & (packet_list.size() - 1);
//		start_idx -= packet_list.size() <= start_idx ? packet_list.size() : 0;

		FecPacket *packet = packet_list[start_idx].get();
		if (!packet->source)
			continue;
			
		if (!(packet->status & kInserted) || packet->status & kDelivered)
			continue;

		if (packet->frame_begin && (packet->status & kDecoded)) {
			next_frame_idx = start_idx;
			timestamp = packet->timestamp;
			break;
		}
	}

	if (next_frame_idx == index || packet_list.size() == next_frame_idx)
		return;

	LOG(LS_WARNING) << "reset frame: index " << index << " next frame " << next_frame_idx;
	ResetNextFecPacket(index, next_frame_idx);
	ResetPreviousFecPacket(index, timestamp);
	last_frame_idx = next_frame_idx;
}

void RtcFecDecoder::ResetNextFecPacket(const uint32_t start_idx, const uint32_t end_idx)
{
	uint32_t packet_num = end_idx >= start_idx ? (end_idx - start_idx)
												  : (end_idx + packet_list.size() - start_idx);

	uint32_t loop = 0;
	while (packet_num > loop) {
		uint32_t index = (start_idx + (loop++)) & (packet_list.size() - 1);
		FecPacket *packet = packet_list[index].get();
		if (!(packet->status & kInserted))
			continue;

		packet->status = 0;		
		if (packet->source && MaxSize() >= packet->size) {
			callback_->ReceivePacket(packet->data + MinSize(), packet->size - MinSize());
			LOG(LS_WARNING) << "reset frame: deliver index " << index
							<< " seq " << rtc::GetBE16(packet->data + 2)
							<< " ssrc " << rtc::GetBE32(packet->data + 8)
							<< " timestamp " << packet->timestamp;
		}
	}
}

void RtcFecDecoder::ResetPreviousFecPacket(const uint32_t index, const uint32_t timestamp)
{
	uint32_t loop = 0;
	uint32_t start_idx = index;
	while (packet_list.size() > loop) {
		loop++;
		start_idx = start_idx ? (start_idx - 1) : (packet_list.size() - 1);
		FecPacket *packet = packet_list[start_idx].get();
		if ((packet->status & kInserted) && (packet->status & kDelivered) && 
				(packet->timestamp < timestamp)) {
			packet->status = 0;
			LOG(LS_WARNING) << "reset frame: decoded index " << start_idx
							<< " seq " << rtc::GetBE16(packet->data + 2)
							<< " ssrc " << rtc::GetBE32(packet->data + 8)
							<< " timestamp " << packet->timestamp;	
		}
	}
}

int RtcFecDecoder::CreateFecInstance(const uint32_t rows, const uint32_t columns)
{
	param_.nb_source_symbols = columns;
	param_.nb_repair_symbols = rows - columns;
	
	const of_codec_id_t codec_id = OF_CODEC_REED_SOLOMON_GF_2_M_STABLE;
	if (0 == of_create_codec_instance(&session, codec_id, OF_DECODER, 2)
		&& 0 == of_set_fec_parameters(session, (of_parameters_t*)&param_))
		return 0;

	return -1;	
}
