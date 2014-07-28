//
//  MediaSample.cpp
//  RtcSameple
//
//  Created by raymon_wang on 14-7-24.
//  Copyright (c) 2014年 yunwei. All rights reserved.
//

#include "MediaSample.h"

using namespace webrtc;

MediaSample::MediaSample() //:
//_voiceEngine(NULL)
{
//    _voiceEngine = new cricket::WebRtcVoiceEngine();
    _voe = VoiceEngine::Create();
    _voe_base = VoEBase::GetInterface(_voe);
    _voe_base->Init();
    int ch = _voe_base->CreateChannel();
    _voe_base->StartPlayout(ch);
}

MediaSample::~MediaSample()
{
    
}

void MediaSample::init()
{
//    if (_voiceEngine) {
//        _voiceEngine->SetAudioDeviceModule(_audioModule.get(), NULL);
//    }
}




