//
//  MediaSample.h
//  RtcSameple
//
//  Created by raymon_wang on 14-7-24.
//  Copyright (c) 2014年 yunwei. All rights reserved.
//

#ifndef __RtcSameple__MediaSample__
#define __RtcSameple__MediaSample__

#include <iostream>
//#include <talk/media/webrtc/webrtcvoiceengine.h>
#include <webrtc/voice_engine/include/voe_base.h>

class MediaSample {
public:
    MediaSample();
    virtual ~MediaSample();
    
    void init();
    
protected:
//    cricket::WebRtcVoiceEngine*     _voiceEngine;
//    talk_base::scoped_refptr<webrtc::AudioDeviceModule>    _audioModule;
    webrtc::VoiceEngine*            _voe;
    webrtc::VoEBase*                _voe_base;
};

#endif /* defined(__RtcSameple__MediaSample__) */
