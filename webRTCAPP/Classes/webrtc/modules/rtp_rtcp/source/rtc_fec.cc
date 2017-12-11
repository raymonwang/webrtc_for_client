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
	InitFecHeader(buffer, current_seq, ssrc);
	uint32_t len = sizeof(FecHeader);
	
	// set payload length
	rtc::SetBE32(buffer + len, size);
	len += sizeof(uint32_t);

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
			InitFecHeader(packet_list[i].get(), current_seq, ssrc);
			current_seq++;

			of_build_repair_symbol(session, (void**)packet_pointer, i);
			callback_ ? callback_->SendPacket(packet_list[i].get(), MaxSize()) : 0;
		}
	}

	received_num = 0;
	return true;
}

void RtcFecEncoder::InitFecHeader(uint8_t *buffer, const uint16_t seq_num,
								  const uint32_t ssrc)
{
	// fec header is like rtp header, so when received fec packet, remote can see
	// who send this packet by ssrc
	FecHeader *header =(FecHeader*)buffer;
	header->version = 0x80;
	header->pt = 0x4d;
	rtc::SetBE16(&header->seq_num, seq_num);

	// reserved for fec encoder info: source num, repair num, max length
	rtc::SetBE32(&header->info, 0);
	rtc::SetBE32(&header->ssrc, ssrc);
}

/*
int RtcFecEncoder::GetFecPacket(const uint32_t index, uint8_t** data, uint32_t& size)
{
	if (index >= Rows())
		return -1;

	*data = packet_list[index].get();
	size = sizeof(FecHeader) + sizeof(uint32_t);
	size += (index >= Columns()) ? MaxSize()
								 : ntohl(((uint32_t*)(*data + sizeof(FecHeader)))[0]);
	return 0;
}
*/

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
	if (0 != CreateFecInstance(source_num, repair_num, max_length))
		return -1;
	
	fec_pointer = (uint8_t**)(new uint8_t[Rows() * sizeof(uint8_t*)]);
	raw_pointer = (uint8_t**)(new uint8_t[Rows() * sizeof(uint8_t*)]);
	if (!fec_pointer || !raw_pointer)
		return -1;

	uint32_t size = max_length + sizeof(FecHeader) + sizeof(uint32_t);
	for (uint32_t i = 0; i < Rows(); i++) {
		fec_pointer[i] = raw_pointer[i] = nullptr;
		
		std::unique_ptr<uint8_t> packet(new uint8_t[size]);
		packet_list.emplace_back(false, std::move(packet));
	}
		
	return 0;
}

bool RtcFecDecoder::InsertFecData(const uint8_t *data, const uint32_t size)
{	
	uint16_t seq_num = rtc::GetBE16(data + sizeof(uint16_t));
	if (0 == start_seq)
		start_seq = Rows() * (seq_num / Rows());

//	LOG(LS_WARNING) << "Insert fec data: seq " << seq_num << ", start seq " << start_seq;
	// have received all source packet OR loss source packet have reconstructed
	// drop remnant repair packet
	if (start_seq > seq_num)
		return false;

	// next array is coming, but this array have not reconstructed
	if (seq_num >= (start_seq + Rows())) {
		LOG(LS_WARNING) << "Next array of fec packet is coming";
		DecodedSection();
		WriteFecData(seq_num, data, size);
		return true;
	}

	WriteFecData(seq_num, data, size);
	if (Columns() > received_num)
		return false;

	Decoded();
	return true;

/*
	if (of_decode_with_new_symbol(session, buffer + sizeof(FecHeader), index) != OF_STATUS_ERROR)
		received++;

	if (received < Columns() || !of_is_decoding_complete(session))
		return false;

	of_finish_decoding(session);
	if (of_get_source_symbols_tab(session, (void**)raw_pointer) != OF_STATUS_OK) {
		printf("get source symbols failed \n");
	}

	of_release_codec_instance(session);
	session = nullptr;
	// refresh start sequence number
	start_seq += Rows();
	received = 0;
*/
}

void RtcFecDecoder::WriteFecData(const uint16_t seq, const uint8_t *data,
								 const uint32_t size)
{
	if (MaxSize() < size) {
		LOG(LS_ERROR) << "fec data size " << size << " is too larger";
		return;
	}
	
	uint16_t index = seq % Rows();	
	uint8_t *buffer = packet_list[index].second.get();
	memcpy(buffer, data, size);
	if (MaxSize() > size)
		memset(buffer + size, 0x0, MaxSize() - size);

	packet_list[index].first = true;
	fec_pointer[index] = buffer + sizeof(FecHeader);
//	LOG(LS_WARNING) << "Write fec data: seq " << seq << ", index " << index
//					<< ", size is " << size;
	received_num++;	
}

int RtcFecDecoder::Decoded()
{
	//for (size_t i = 0; i < packet_list.size(); i++) {
	//	fec_pointer[i] = packet_list[i].first ? (packet_list[i].second.get() + sizeof(FecHeader))
	//										  : nullptr;
	//	if (!fec_pointer[i])
	//		LOG(LS_WARNING) << "index " << i << " is null pointer";
	//}

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

	for (size_t i = 0; i < Columns() && callback_; i++) {
		if (raw_pointer[i]) {
			uint32_t size = rtc::GetBE32(raw_pointer[i]);
//			LOG(LS_WARNING) << "send to vie: index " << i << " pointer " << raw_pointer[i]
//							<< " size " << size;
			callback_->ReceivePacket(raw_pointer[i] + sizeof(uint32_t), size);

			// memory malloc by openfec
			if (!fec_pointer[i])
				free(raw_pointer[i]);
		}
	}

	of_release_codec_instance(session);
	session = nullptr;

	CreateFecInstance(kFecSourceNum, kFecRepairNum, kFecMaxLength);
	// set packet list free
	for (size_t i = 0; i < Rows(); i++)
		packet_list[i].first = false;
	
	// refresh start sequence number
	start_seq += Rows();
	received_num = 0;	
	return 0;
}

int RtcFecDecoder::DecodedSection()
{
	for (uint32_t i = 0; i < Columns() && callback_; i++) {
		if (!packet_list[i].first)
			continue;

		uint8_t *buffer = packet_list[i].second.get() + sizeof(FecHeader);
		uint32_t size = rtc::GetBE32(buffer);
		callback_->ReceivePacket(buffer + sizeof(uint32_t), size);
	}

	
	of_finish_decoding(session);
	of_release_codec_instance(session);
	session = nullptr;
	
	// set packet list free
	for (size_t i = 0; i < Rows(); i++)
		packet_list[i].first = false;
	
	// refresh start sequence number
	start_seq += Rows();
	received_num = 0;	
	return 0;
}

/*
int RtcFecDecoder::GetRawPacket(const uint32_t index, uint8_t **data, uint32_t& size)
{
	if (index >= Columns())
		return -1;

	if (!packet_list[index].first)
		return -1;
	
	*data = packet_list[index].second.get() + sizeof(FecHeader);;
	if (*data) {
		size = ntohl(((uint32_t*)(*data))[0]);
		*data += sizeof(uint32_t);
	}

	packet_list[index].first = false;
	return 0;
}
*/

int RtcFecDecoder::CreateFecInstance(const uint32_t source_num,
									 const uint32_t repair_num,
									 const uint32_t max_length)
{
	param.nb_source_symbols = source_num;
	param.nb_repair_symbols = repair_num;
	param.encoding_symbol_length = max_length + sizeof(int);
	param.m = 8;
	
	const of_codec_id_t codec_id = OF_CODEC_REED_SOLOMON_GF_2_M_STABLE;
	if (0 == of_create_codec_instance(&session, codec_id, OF_DECODER, 2)
		&& 0 == of_set_fec_parameters(session, (of_parameters_t*)&param))
		return 0;

	return -1;	
}