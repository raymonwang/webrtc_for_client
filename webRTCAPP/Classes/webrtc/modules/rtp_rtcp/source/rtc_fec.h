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
#include "webrtc/base/buffer.h"
#include "webrtc/base/criticalsection.h"
#include "webrtc/base/platform_thread.h"
#include "webrtc/system_wrappers/include/sleep.h"
#include "webrtc/system_wrappers/include/event_wrapper.h"

extern "C" {
#include "third_party/openfec/src/lib_common/of_openfec_api.h"
} 

using namespace std;
using namespace rtc;
using namespace webrtc;

const uint32_t kFecSourceNum = 12;
const uint32_t kFecRepairNum = 3;
const uint32_t kFecMaxLength = 1200;

struct FecHeader {
	uint8_t		version;
	uint8_t 	pt;
	uint16_t 	seq_num;
	uint32_t	info;
	uint32_t	ssrc;
	uint8_t		sources;
	uint8_t		repairs;
	uint16_t	start_seq;
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
		: start_seq(0),
		current_seq(0),
		last_encoded_timestamp(0),
		highest_seq_num_(0),
		cumulative_lost_(0),
		repair_need(0),
		last_zero_repair_time(0),
		session(nullptr),
		callback_(callback) { }
	
	~RtcFecEncoder();

	static RtcFecEncoder* Create(const uint32_t source_num, 
								 const uint32_t repair_num,
								 const uint32_t max_length,
								 RtcFecEncoderCallback *callback);
	
	int Init(const uint32_t source_num, const uint32_t repair_num, 
			 const uint32_t max_length);
	
	bool InsertPacket(const uint8_t *data, const uint32_t size);
  	bool OnReceiveReport(const uint32_t cumulative_lost, const uint16_t highest_seq_num);

  private:
  	Buffer* GetPacket();
	void WriteFecSourcePacket(Buffer *packet, const uint8_t *data, const uint32_t size);
	int SendFecRepairPacket(const uint32_t ssrc, const uint32_t timestamp);
	void RecyclePacket();
	int CreateFecInstance();
	void InitFecHeader(uint8_t *buffer, const uint32_t ssrc, const uint32_t timestamp);
	inline uint32_t MaxSize() { return param.encoding_symbol_length + sizeof(FecHeader); }
//	inline uint32_t Columns() { return param.nb_source_symbols; }
//	inline uint32_t Rows() { return param.nb_source_symbols + param.nb_repair_symbols; }

	uint16_t start_seq;
	uint16_t current_seq;
	uint32_t last_encoded_timestamp;

	uint32_t highest_seq_num_;
	uint32_t cumulative_lost_;
	uint32_t repair_need;
	int64_t  last_zero_repair_time;
	
  	of_session_t *session;
	of_rs_2_m_parameters_t param;
	RtcFecEncoderCallback *callback_;
	std::list<Buffer*> free_list;
	std::vector<Buffer*> packet_list; 
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
	struct FecPacket {
		FecPacket() 
			: status(0),
			timestamp(0),
			start_seq(0),
			source_num(0),
			repair_num(0),
			source(false),
			frame_begin(false),
			frame_end(false),
			size(0) {}

		uint32_t 	status;
		uint32_t	timestamp;
		uint32_t	start_seq;
		uint32_t	source_num;
		uint32_t	repair_num;
		bool		source;
		bool		frame_begin;
		bool		frame_end;
		uint8_t		data[1500];  // should be larger than MaxSize()
		uint32_t	size;
	};
	
	RtcFecDecoder(RtcFecDecoderCallback *callback)
		: last_decoded_timestamp(0), 
//		last_insert_timestamp(0),
		last_decoded_idx(0),
		last_frame_idx(0),
		fec_pointer(nullptr),
		raw_pointer(nullptr),
		session(nullptr),
		callback_(callback),
		event_(EventWrapper::Create()),
		worker(new PlatformThread(Runnable, this, "FecDecoder")),
		lock(new CriticalSection()){ }
	
	~RtcFecDecoder();

	static RtcFecDecoder* Create(const uint32_t source_num,
								 const uint32_t repair_num,
						  		 const uint32_t max_length,
						  		 RtcFecDecoderCallback *callback);
	
	int Init(const uint32_t source_num, const uint32_t repair_num, 
			 const uint32_t max_length);

	static bool Runnable(void *obj);
	int InsertFecData(const uint8_t *data, const uint32_t size);

  private:
  	void FreeFecSequence(const FecHeader *header);
	bool NeedToInsert(const FecHeader *header);
	bool NeedSetEvent(const FecHeader *header);
	void WriteFecData(const uint32_t index, const uint8_t *data,
					  const uint32_t size);
  	void Process();
	int DecodedFec();
	uint32_t FindNextSequence(uint32_t index);
//	void DecodedLastPacket(const uint32_t index);
	bool DecodedPacket(const uint32_t index, const uint32_t rows);
	int Decoded(const uint32_t index, const uint32_t rows, const uint32_t columns);
	int ResetDecoder(const uint32_t index, const uint32_t rows, const uint32_t columns);
	int CreateFecInstance(const uint32_t rows, const uint32_t columns);
	void DeliverFrame();
	uint32_t DeliverPacket(const uint32_t start_idx, const uint32_t end_idx);
	uint32_t GetCompleteFrame(const uint32_t index);
	void ResetNotCompleteFrame(const uint32_t index);
	void ResetNextFecPacket(const uint32_t start_idx, const uint32_t end_idx);
	void ResetPreviousFecPacket(const uint32_t index, const uint32_t timestamp);


  	inline uint32_t MaxSize() { return param_.encoding_symbol_length + sizeof(FecHeader); }
	inline uint32_t MinSize() { return sizeof(FecHeader) + sizeof(uint32_t); }

	enum { kInserted = 0x1, kDecoded = 0x10, kDelivered = 0x100, kReleased = 0x111 };

	uint32_t  last_decoded_timestamp;
//	uint32_t  last_insert_timestamp;
	uint32_t  last_decoded_idx;
	uint32_t  last_frame_idx;	
	uint8_t** fec_pointer;
	uint8_t** raw_pointer;
  	of_session_t *session;
	of_rs_2_m_parameters_t param_;

	RtcFecDecoderCallback *callback_;
	std::unique_ptr<EventWrapper> event_;
	std::unique_ptr<PlatformThread> worker;
	std::unique_ptr<CriticalSection> lock;
	std::vector<std::unique_ptr<FecPacket>> packet_list;
};

#endif
