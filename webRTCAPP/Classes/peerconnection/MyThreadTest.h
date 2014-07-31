//
//  MyThreadTest.h
//  webRTCAPP
//
//  Created by raymon_wang on 14-7-31.
//  Copyright (c) 2014年 yunwei. All rights reserved.
//

#ifndef __webRTCAPP__MyThreadTest__
#define __webRTCAPP__MyThreadTest__

#include <iostream>
#include "webrtc/system_wrappers/interface/thread_wrapper.h"

using namespace webrtc;

class MyThreadTest {
public:
    MyThreadTest();
    virtual ~MyThreadTest();
    
    bool Process();
    
    static bool Run(ThreadObj obj);
    
private:
    ThreadWrapper*      _threadWrapper;
};

#endif /* defined(__webRTCAPP__MyThreadTest__) */
