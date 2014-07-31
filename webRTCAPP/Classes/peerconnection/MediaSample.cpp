//
//  MediaSample.cpp
//  RtcSameple
//
//  Created by raymon_wang on 14-7-24.
//  Copyright (c) 2014年 yunwei. All rights reserved.
//

#include "MediaSample.h"
#include "MyThreadTest.h"

using namespace webrtc;

MediaSample::MediaSample() //:
//_voiceEngine(NULL)
{
//    _voiceEngine = new cricket::WebRtcVoiceEngine();
    _voe = VoiceEngine::Create();
    _voe_base = VoEBase::GetInterface(_voe);
    _voe_base->Init();
    
    
    int sendch = _voe_base->CreateChannel();
//    int recvch = _voe_base->CreateChannel();
    
    VoENetwork* network = VoENetwork::GetInterface(_voe);
    
    _voiceSendTransport = new VoiceChannelTransport(network, sendch);
//    _voiceRecvTransport = new VoiceChannelTransport(network, recvch);
    
//    _voiceSendTransport->SetSendDestination("192.168.209.93", 10086);
//    _voiceSendTransport->SetLocalReceiver(20001);
    
//    _voiceSendTransport->SetSendDestination("192.168.208.6", 20001);
//    _voiceSendTransport->SetLocalReceiver(10086);
    
//    _voiceSendTransport->SetSendDestination("180.168.126.249", 10086);
//    _voiceSendTransport->SetSendDestination("180.168.126.249", 45001);
    _voiceSendTransport->SetSendDestination("180.168.126.253", 20002);
    _voiceSendTransport->SetLocalReceiver(20000);
    
//    _voiceRecvTransport->SetSendDestination("180.168.126.249", 10086);
//    _voiceRecvTransport->SetLocalReceiver(20001);
    
//    webrtc::Config config;
//    _channelManager = new ChannelManager(0, config);
//    int cid = _channelManager->CreateChannel().channel()->ChannelId();
//    _channelManager->GetChannel(cid).channel()->StartSend();
    
    _myThreadTest = new MyThreadTest;
    
    init();
}

MediaSample::~MediaSample()
{
    
}

void MediaSample::init()
{
//    if (_voiceEngine) {
//        _voiceEngine->SetAudioDeviceModule(_audioModule.get(), NULL);
//    }
    VoECodec* codec = VoECodec::GetInterface(_voe);
    
    CodecInst inst;
    
    int num = codec->NumOfCodecs();
    for (int i = 0; i < num; i++) {
        codec->GetCodec(i, inst);
        printf("%s\n", inst.plname);
        if (inst.pltype == 102) {
            codec->SetSendCodec(0, inst);
            break;
        }
    }
    
    VoEHardware* hardware = VoEHardware::GetInterface(_voe);
    hardware->SetLoudspeakerStatus(true);
    
//    VoERTP_RTCP* rtcp = VoERTP_RTCP::GetInterface(_voe);
//    rtcp->SendApplicationDefinedRTCPPacket(0, 1, 1, "lwangxin", 8);
    
//    VoEVolumeControl* volumnControl = VoEVolumeControl::GetInterface(_voe);
//    unsigned int volumn;
//    volumnControl->GetSpeakerVolume(volumn);
//    volumnControl->SetSpeakerVolume(volumn*10);
//    volumnControl->SetChannelOutputVolumeScaling(0, 5);
    
    _voe_base->StartPlayout(0);
    _voe_base->StartReceive(0);
    _voe_base->StartSend(0);
    
    
    _voe_base->SetNetEQPlayoutMode(0, kNetEqDefault);
    
    _voe_base->RegisterVoiceEngineObserver(*this);
}

void MediaSample::CallbackOnError(int channel, int errCode)
{
    printf("channel=%d, errCode=%d", channel, errCode);
}

int MediaSample::ReceivedRTPPacket(int channel, const void *data, unsigned int length)
{
    VoENetwork* network = VoENetwork::GetInterface(_voe);
    
    return network->ReceivedRTPPacket(2, data, length);
}




