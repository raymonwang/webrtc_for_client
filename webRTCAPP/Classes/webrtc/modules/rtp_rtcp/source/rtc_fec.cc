/*
*
*
*  Copyright by ztgame@2017
*  Written by lfz 
*
*
*/

#include "rtc_fec.h"

RtcFecEncoder::~RtcFecEncoder()
{
	if (session) {
		of_release_codec_instance(session);
		session = nullptr;
	}
		
	if (packet_pointer) {
		delete[] packet_pointer;
		packet_pointer = nullptr;
	}
		
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
	if (0 != CreateFecInstance(source_num, repair_num, max_length))
		return -1;
	
	// start sequence number must be a multiple of Rows()
	current_seq = Rows() * 100;

	packet_pointer = (uint8_t**)(new uint8_t[Rows() * sizeof(uint8_t*)]);

	int size = max_length + sizeof(FecHeader) + sizeof(uint32_t);
	for (size_t i = 0; i < Rows(); i++)
		packet_list.emplace_back(new uint8_t[size]);

	return 0;
}

bool RtcFecEncoder::InsertPacket(const uint8_t *data, const uint32_t size)
{	
	uint16_t index = current_seq % Rows();
	uint8_t *buffer = packet_list[index].get();

	uint32_t ssrc = rtc::GetBE32(data + 8);
	uint32_t timestamp = rtc::GetBE32(data + 4);
	InitFecHeader(buffer, current_seq, ssrc, timestamp);
	uint32_t len = sizeof(FecHeader);
	
	// set payload length
	buffer[len++] = last_encoded_timestamp != timestamp;
	buffer[len++] = data[1] & 0x80 ? 1 : 0;
	last_encoded_timestamp = timestamp;
	rtc::SetBE16(buffer + len, (uint16_t)size);
	len += sizeof(uint16_t);

	// set payload value
	memcpy(buffer + len, data, size);
	len += size;
	if (MaxSize() > len)
		memset(buffer + len, 0x0, MaxSize() - len);
	
	current_seq++;
	received_num++;
	callback_ ? callback_->SendPacket(buffer, len) : 0;
	if (Columns() > received_num)
		return false;

	for (uint32_t i = 0; i < Rows(); i++) {
		// fec encoded payload length and payload value
		packet_pointer[i] = packet_list[i].get() + sizeof(FecHeader);

		if (Columns() <= i) {
			InitFecHeader(packet_list[i].get(), current_seq, ssrc, timestamp - 100);
			current_seq++;

			of_build_repair_symbol(session, (void**)packet_pointer, i);
			callback_ ? callback_->SendPacket(packet_list[i].get(), MaxSize()) : 0;
		}
	}

	received_num = 0;
	return true;
}

void RtcFecEncoder::InitFecHeader(uint8_t *buffer, const uint16_t seq_num,
								  const uint32_t ssrc, const uint32_t timestamp)
{
	// fec header is like rtp header, so when received fec packet, remote can see
	// who send this packet by ssrc
	FecHeader *header =(FecHeader*)buffer;
	header->version = 0x80;
	header->pt = 0x4d;
	rtc::SetBE16(&header->seq_num, seq_num);

	// reserved for fec encoder info: source num, repair num, max length
	rtc::SetBE32(&header->info, timestamp);
	rtc::SetBE32(&header->ssrc, ssrc);
}

int RtcFecEncoder::CreateFecInstance(const uint32_t source_num,
									 const uint32_t repair_num,
									 const uint32_t max_length)
{
	param.nb_source_symbols = source_num;
	param.nb_repair_symbols = repair_num;
	param.encoding_symbol_length = max_length + sizeof(int);
	param.m = 8;
	
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
	param.nb_source_symbols = source_num;
	param.nb_repair_symbols = repair_num;
	param.encoding_symbol_length = max_length + sizeof(int);
	param.m = 8;
	
	fec_pointer = (uint8_t**)(new uint8_t[Rows() * sizeof(uint8_t*)]);
	raw_pointer = (uint8_t**)(new uint8_t[Rows() * sizeof(uint8_t*)]);
	if (!fec_pointer || !raw_pointer) {
		LOG(LS_ERROR) << "malloc pointer for fec decoder failed";
		return -1;
	}

	for (uint32_t i = 0; i < Rows(); i++)
		fec_pointer[i] = raw_pointer[i] = nullptr;

	if (!worker || !lock) {
		LOG(LS_ERROR) << "fec decoder worker or lock didn't startup";
		return -1;
	}

	worker->Start();
	
//	uint32_t size = max_length + sizeof(FecHeader) + sizeof(uint32_t);
	for (uint32_t i = 0; i < Rows() * 5; i++) 		
		packet_list.emplace_back(new FecPacket());
		
	return 0;
}

int RtcFecDecoder::InsertFecData(const uint8_t *data, const uint32_t size)
{
	if (MaxSize() < size || MinSize() >= size) {
		LOG(LS_WARNING) << "Insert fec data, size " << size << " is invalid";
		return -1;
	}
	
	uint16_t recv_seq = rtc::GetBE16(data + 2);
	uint32_t recv_timestamp = rtc::GetBE32(data + 4);

	CritScope cs(lock.get());
	// this sequence fec packet have reconstructed, drop remain fec packet
	if (recv_timestamp < last_decoded_timestamp)
		return 0;

	size_t index = recv_seq % packet_list.size();
	FecPacket *packet = packet_list[index].get();
	if (packet->status) {
		LOG(LS_WARNING) << "new packet " << recv_seq << " is coming, flush old buffer"
						<< " index " << index << " status is " << packet->status;

		ResetFecPacket(index);
	}
	
	memcpy(packet->data, data, size);
	if (MaxSize() > size)
		memset(packet->data + size, 0x0, MaxSize() - size);
	packet->size = size;
	
	packet->status |= kInserted;
	bool source = Source(index);
	packet->frame_begin = source ? data[sizeof(FecHeader)] : true;
	packet->frame_end = source ? data[sizeof(FecHeader) + 1] : true;
	packet->timestamp = source ? rtc::GetBE32(data + MinSize() + 4) : 0;

	// received the k source packet OR received repair packet
	// OR received frame_end packet, SET event
	if (packet->frame_end || param.nb_source_symbols == (index % Rows()))	
		event_->Set();
	
	LOG(LS_WARNING) << "insert " << (source ? "SS" : "RR")
					<< ", index " << index << " fec seq " << recv_seq
					<< " rtp seq " << rtc::GetBE16(data + MinSize() + 2)
					<< " timestamp " << packet->timestamp
					<< " frame [" << packet->frame_begin
					<< " " << packet->frame_end << "]";
	return 0;
}

bool RtcFecDecoder::Runnable(void *obj)
{
	static_cast<RtcFecDecoder*>(obj)->Process();
	return true;
}

void RtcFecDecoder::Process()
{
//	SleepMs(20);
	EventTypeWrapper ev_type = event_->Wait(40);
	if (kEventSignaled == ev_type || kEventTimeout == ev_type) {
		CritScope cs(lock.get());
		DecodedFec();
		DeliverPacket();
	}
}

int RtcFecDecoder::DecodedFec()
{
	uint32_t loop = 0;
	while (packet_list.size() > loop) {
		uint32_t start_idx = loop;
		loop += Rows();

		uint32_t received_num = 0;
		bool all_source_received = true;
		for (size_t i = 0; i < Rows(); i++) {
			FecPacket *packet = packet_list[start_idx + i].get();
			if (packet->status & kDecoded) {
				received_num = 0;
				break;
			}

			received_num += (packet->status & kInserted);
			if (0 == packet->status && i < Columns())
				all_source_received = false;
		}

		if (Columns() <= received_num) {
			all_source_received ? 0 : Decoded(start_idx);
			ResetDecoder(start_idx);
			
			LOG(LS_WARNING) << "Decoded fec: start index " << start_idx;
		}
	}

/*
	uint32_t start_idx = FindEarliestPacket();
	if (packet_list.size() <= start_idx)
		return -1;

	uint32_t loop = 0;
	while (packet_list.size() > loop) {
		uint32_t received_packet = 0;
		bool source_all_received = true;
		for (size_t i = 0; i < Rows(); i++) {
			FecPacket *packet = packet_list[start_idx + i].get();
			received_packet += packet->used && !(packet->status & kHaveDecoded);
			source_all_received = (i < Columns() && !packet->used) ? false
																  : source_all_received;
		}

		// this fec sequence have received k packets
		if (Columns() <= received_packet) {
			source_all_received ? 0 : Decoded(start_idx);
			ResetDecoder(start_idx);
		}
					
		start_idx += Rows();
		start_idx = packet_list.size() <= start_idx ? 0 : start_idx;
		loop += Rows();
	}
*/
	return 0;
}

int RtcFecDecoder::Decoded(const uint32_t index)
{
	uint32_t start_idx = index - index % Rows();

	for (size_t i = 0; i < Rows(); i++) {
		FecPacket *packet = packet_list[start_idx + i].get();
		fec_pointer[i] = (packet->status & kInserted) ? (packet->data + sizeof(FecHeader))
													  : nullptr;
	}

	if (0 != CreateFecInstance()) {
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

	for (size_t i = 0; i < Columns(); i++) {
		if (raw_pointer[i] && !fec_pointer[i]) {
			FecPacket *packet = packet_list[start_idx + i].get();
			packet->status |= kInserted;
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

int RtcFecDecoder::ResetDecoder(const uint32_t index)
{
	if (session) {
		of_release_codec_instance(session);
		session = nullptr;
	}

	uint32_t start_idx = index - index % Rows();
	for (size_t i = 0; i < Rows(); i++) {
		fec_pointer[i] = nullptr;
		raw_pointer[i] = nullptr;

		FecPacket *packet = packet_list[start_idx +i].get();
		if (Columns() <= i)
			packet->status = 0;
		else {
			packet->status |= kDecoded;
			if (kReleased == packet->status)
				packet->status = 0;			
		}
	}

	size_t last_source_idx = start_idx + Columns() - 1;
	uint32_t timestamp = packet_list[last_source_idx]->timestamp;
	last_decoded_timestamp = std::max(timestamp, last_decoded_timestamp);
	return 0;
}

int RtcFecDecoder::ResetFecPacket(const uint32_t index)
{
	uint32_t start_idx = index - index % Rows();
	for (size_t i = 0; i < Rows(); i++) {
		fec_pointer[i] = nullptr;
		raw_pointer[i] = nullptr;

		FecPacket *packet = packet_list[start_idx +i].get();
		if (i < Columns() && (packet->status & kInserted) &&
			!(packet->status & kDelivered)) {
			LOG(LS_WARNING) << "reset fec packet, deliver index " << (start_idx + i);
			callback_->ReceivePacket(packet->data + MinSize(),
									 packet->size - MinSize());
		}

		packet->status = 0;
	}

	return 0;
}

void RtcFecDecoder::DeliverPacket()
{
	for (size_t i = 0; i < packet_list.size(); i++) {
		FecPacket *packet = packet_list[i].get();
		if (!Source(i) || !packet->frame_begin)
			continue;

		if (!(packet->status & kInserted) || packet->status & kDelivered)
			continue;

		std::vector<FecPacket*> frame = GetPacketsInFrame(i, packet->timestamp);
		for (size_t k = 0; k < frame.size() && callback_; k++) {
			uint8_t *data = frame[k]->data + MinSize();
			uint32_t size = frame[k]->size - MinSize();
			callback_->ReceivePacket(data, size);

			frame[k]->status |= kDelivered;
			if (kReleased == frame[k]->status)
				frame[k]->status = 0;
		}
	}
}

std::vector<RtcFecDecoder::FecPacket*> RtcFecDecoder::GetPacketsInFrame(
								const uint32_t index, const uint32_t timestamp)
{
	bool find_end = false;
	uint32_t loop = 0;
	uint32_t end_idx = index;
	std::vector<FecPacket*> frame;

	while (packet_list.size() > loop) {
		++loop;

		FecPacket *packet = packet_list[end_idx].get();
		// skip repair packet
		if (!Source(end_idx)) {
			end_idx = (++end_idx >= packet_list.size()) ? 0 : end_idx;
			continue;
		}
			
		// have loss packet OR have no frame end packet
		if (!(packet->status & kInserted) || timestamp != packet->timestamp) {
			frame.clear();
			break;
		}

		frame.push_back(packet);
		// seek to frame end packet
		if (packet->frame_end) {
			find_end = true;
			break;
		}

		end_idx = (++end_idx >= packet_list.size()) ? 0 : end_idx;
	}

	if (!find_end)
		frame.clear();

	if (!frame.empty())
		LOG(LS_WARNING) << "get frame: index " << index << ", size " << frame.size();
	return frame;
}

uint32_t RtcFecDecoder::FindEarliestPacket()
{
/*
	uint32_t start_idx = packet_list.size();
	uint32_t earliest_timestamp = 0xffffffff;
	for (size_t i = 0; i < packet_list.size(); i += Rows()) {
		FecPacket *packet = packet_list[i].get();
		if (packet->used && packet->source && !(packet->status & kHaveDecoded) &&
            packet->timestamp < earliest_timestamp) {
			earliest_timestamp = packet->timestamp;
			start_idx = i;
		}
	}

	if (packet_list.size() > start_idx)
		start_idx -= (start_idx % Rows());
	return start_idx;
*/
	return packet_list.size();
}

int RtcFecDecoder::CreateFecInstance()
{	
	const of_codec_id_t codec_id = OF_CODEC_REED_SOLOMON_GF_2_M_STABLE;
	if (0 == of_create_codec_instance(&session, codec_id, OF_DECODER, 2)
		&& 0 == of_set_fec_parameters(session, (of_parameters_t*)&param))
		return 0;

	return -1;	
}
