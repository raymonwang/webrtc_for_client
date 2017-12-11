/*
*
*
*  Copyright by ztgame@2017
*  Written by lfz 
*
*
*/

#ifndef RTC_FEC_H
#define RTC_FEC_H

#include <vector>
#include <memory>
#include <string.h>
#include "webrtc/base/basictypes.h"
#include "webrtc/base/byteorder.h"
#include <webrtc/base/logging.h>

extern "C" {
#include "third_party/openfec/src/lib_common/of_openfec_api.h"
} 

using namespace std;
using namespace rtc;

const uint32_t kFecSourceNum = 10;
const uint32_t kFecRepairNum = 5;
const uint32_t kFecMaxLength = 1200;

struct FecHeader {
	uint8_t		version;
	uint8_t 	pt;
	uint16_t 	seq_num;
	uint32_t	info;
	uint32_t	ssrc;
};

class RtcFecEncoderCallback
{
  public:
	virtual int SendPacket(const uint8_t *data, const uint32_t size) = 0;
	
  protected:
  	virtual ~RtcFecEncoderCallback() { }
};

class RtcFecEncoder
{
  public:
	RtcFecEncoder(RtcFecEncoderCallback *callback)
		: received_num(0),
		current_seq(0),
		session(nullptr),
		packet_pointer(nullptr),
		callback_(callback) { }
	
	~RtcFecEncoder();

	static RtcFecEncoder* Create(const uint32_t source_num, 
								 const uint32_t repair_num,
								 const uint32_t max_length,
								 RtcFecEncoderCallback *callback);
	
	int Init(const uint32_t source_num, const uint32_t repair_num, 
			 const uint32_t max_length);
	
	bool InsertPacket(const uint8_t *data, const uint32_t size);
	//int GetFecPacket(const uint32_t index, uint8_t **data, uint32_t &size);
	
  private:
	int CreateFecInstance(const uint32_t source_num,
						  const uint32_t repair_num, 
			 			  const uint32_t max_length);
	void InitFecHeader(uint8_t *buffer, const uint16_t seq_num,
							 const uint32_t ssrc);
	inline uint32_t MaxSize() { 
		return param.encoding_symbol_length + sizeof(FecHeader); 
	}
	inline uint32_t Columns() { return param.nb_source_symbols; }
	inline uint32_t Rows() { return param.nb_source_symbols + param.nb_repair_symbols; }

	uint16_t received_num;
	uint16_t current_seq;
  	of_session_t *session;
	of_rs_2_m_parameters_t param;
	
	uint8_t **packet_pointer;
	RtcFecEncoderCallback *callback_;
	std::vector<std::unique_ptr<uint8_t>> packet_list; 
};


class RtcFecDecoderCallback
{
  public:
	virtual int ReceivePacket(const uint8_t *data, const uint32_t size) = 0;
	
  protected:
  	virtual ~RtcFecDecoderCallback() { }
};

class RtcFecDecoder
{
  public:
	RtcFecDecoder(RtcFecDecoderCallback *callback)
		: start_seq(0),
		received_num(0),
		fec_pointer(nullptr),
		raw_pointer(nullptr),
		session(nullptr),
		callback_(callback) { }
	
	~RtcFecDecoder();

	static RtcFecDecoder* Create(const uint32_t source_num,
								 const uint32_t repair_num,
						  		 const uint32_t max_length,
						  		 RtcFecDecoderCallback *callback);
	
	int Init(const uint32_t source_num, const uint32_t repair_num, 
			 const uint32_t max_length);
	
	bool InsertFecData(const uint8_t *data, const uint32_t size);
//	int GetRawPacket(const uint32_t index, uint8_t **data, uint32_t& size);

  private:
  	int Decoded();
	int DecodedSection();
	int CreateFecInstance(const uint32_t source_num, 
						  const uint32_t repair_num, 
			 			  const uint32_t max_length);
	void WriteFecData(const uint16_t seq, const uint8_t *data, const uint32_t size);

  	inline uint32_t MaxSize() { 
		return param.encoding_symbol_length + sizeof(FecHeader); 
	}
	inline uint32_t Rows() { return (param.nb_source_symbols + param.nb_repair_symbols); }
	inline uint32_t Columns() { return param.nb_source_symbols; }
	
	uint16_t start_seq;
	uint32_t received_num;
	
	uint8_t** fec_pointer;
	uint8_t** raw_pointer;
  	of_session_t *session;
	of_rs_2_m_parameters_t param;

	RtcFecDecoderCallback *callback_;
	std::vector<std::pair<bool, std::unique_ptr<uint8_t>>> packet_list;   	
};

#endif
