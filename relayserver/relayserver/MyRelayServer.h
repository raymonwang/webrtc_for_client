//
//  MyRelayServer.h
//  relayserver
//
//  Created by raymon_wang on 14-8-1.
//  Copyright (c) 2014年 yunwei. All rights reserved.
//

#ifndef __relayserver__MyRelayServer__
#define __relayserver__MyRelayServer__

#include <iostream>
#include "talk/base/thread.h"

class MyRelayServer : public talk_base::MessageHandler, public sigslot::has_slots<> {
public:
    MyRelayServer(talk_base::Thread* thread);
    virtual ~MyRelayServer();
    
    talk_base::Thread* thread() { return _thread; }
    
private:
    talk_base::Thread*          _thread;
};

#endif /* defined(__relayserver__MyRelayServer__) */
