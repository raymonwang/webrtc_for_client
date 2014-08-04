//
//  main.cpp
//  relayserver
//
//  Created by raymon_wang on 14-7-24.
//  Copyright (c) 2014年 yunwei. All rights reserved.
//

#include <iostream>
#include "talk/base/thread.h"
#include "talk/base/scoped_ptr.h"
#include "talk/p2p/base/relayserver.h"
#include "talk/p2p/base/turnserver.h"

int main(int argc, const char * argv[])
{
//    if (argc != 3) {
//        std::cerr << "usage: relayserver internal-address external-address"
//        << std::endl;
//        return 1;
//    }
    
    argv[1] = "192.168.82.191:16001";
    argv[2] = "192.168.82.191:16002";
    
    talk_base::SocketAddress data_addr;
    if (!data_addr.FromString(argv[1])) {
        std::cerr << "Unable to parse IP address: " << argv[1];
        return 1;
    }
    
    talk_base::SocketAddress ctr_addr;
    if (!ctr_addr.FromString(argv[2])) {
        std::cerr << "Unable to parse IP address: " << argv[2];
        return 1;
    }
    
    talk_base::Thread *pthMain = talk_base::Thread::Current();
    
//    talk_base::scoped_ptr<talk_base::AsyncUDPSocket> data_socket(talk_base::AsyncUDPSocket::Create(pthMain->socketserver(), data_addr));
//    if (!data_socket) {
//        std::cerr << "Failed to create a UDP socket bound at"
//        << data_addr.ToString() << std::endl;
//        return 1;
//    }
//    
//    talk_base::scoped_ptr<talk_base::AsyncUDPSocket> ctr_socket(talk_base::AsyncUDPSocket::Create(pthMain->socketserver(), ctr_addr));
//    if (!ctr_socket) {
//        std::cerr << "Failed to create a UDP socket bound at"
//        << ctr_addr.ToString() << std::endl;
//        return 1;
//    }
    
    talk_base::AsyncUDPSocket* server_socket =
    talk_base::AsyncUDPSocket::Create(pthMain->socketserver(), data_addr);
    if (!server_socket) {
        std::cerr << "Failed to create a UDP socket" << std::endl;
        return 1;
    }
    
    cricket::TurnServer server(server_socket);
    
//    cricket::RelayServer server(pthMain);
//    
//    server.AddInternalSocket(data_socket.get());
//    server.AddExternalSocket(ctr_socket.get());
//    
//    std::cout << "Listening internally at " << data_addr.ToString() << std::endl;
//    std::cout << "Listening externally at " << ctr_addr.ToString() << std::endl;
    
    pthMain->Run();
    
    return 0;
    return 0;
}

