//
//  MyThreadTest.cpp
//  webRTCAPP
//
//  Created by raymon_wang on 14-7-31.
//  Copyright (c) 2014年 yunwei. All rights reserved.
//

#include "MyThreadTest.h"
#include <unistd.h>

MyThreadTest::MyThreadTest()
{
    _threadWrapper = ThreadWrapper::CreateThread(MyThreadTest::Run, this, kRealtimePriority, "MyThreadTest");
    
    unsigned int id = 0;
    _threadWrapper->Start(id);
}

MyThreadTest::~MyThreadTest()
{
    if(_threadWrapper != NULL)
    {
        delete _threadWrapper;
    }
}

bool MyThreadTest::Process()
{
    static int i = 0;
    printf("%d\n", i++);
    sleep(2);
    
    return true;
}

bool MyThreadTest::Run(void *obj)
{
    MyThreadTest* threadTest = static_cast<MyThreadTest*>(obj);

    return threadTest->Process();
}