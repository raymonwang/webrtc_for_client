//
//  rtpeerconnection.h
//  webRTCAPP
//
//  Created by raymon_wang on 14-7-23.
//  Copyright (c) 2014年 yunwei. All rights reserved.
//

#ifndef __webRTCAPP__rtpeerconnection__
#define __webRTCAPP__rtpeerconnection__

#include <iostream>
#include <map>
#include "../webrtc/base/asyncudpsocket.h"
#include "../webrtc/base/thread.h"
#include "../webrtc/base/messagehandler.h"
#include "../webrtc/base/nethelpers.h"

using namespace rtc;

struct PeerConnectionClientObserver {
    virtual void OnSignedIn() = 0;  // Called when we're logged on.
    virtual void OnDisconnected() = 0;
    virtual void OnPeerConnected(int id, const std::string& name) = 0;
    virtual void OnPeerDisconnected(int peer_id) = 0;
    virtual void OnMessageFromPeer(int peer_id, const std::string& message) = 0;
    virtual void OnMessageSent(int err) = 0;
    virtual void OnServerConnectionFailure() = 0;
    
protected:
    virtual ~PeerConnectionClientObserver() {}
};

class RtpPeerConnection : public sigslot::has_slots<>, public rtc::MessageHandler{
public:
    typedef std::map<int, std::string> Peers;
    
    enum State {
        NOT_CONNECTED,
        RESOLVING,
        SIGNING_IN,
        CONNECTED,
        SIGNING_OUT_WAITING,
        SIGNING_OUT,
    };
    
public:
    RtpPeerConnection();
    ~RtpPeerConnection();
    
    int id() const;
    bool is_connected() const;
    const Peers& peers() const;
    
    void RegisterObserver(PeerConnectionClientObserver* callback);
    
    void Connect(const std::string& server, int port, const std::string& client_name);
    
    bool IsSendingMessage();
    
protected:
    void DoConnect();
    
    void Close();
    
    void InitSocketSignals();
    
    //连接控制通道
    bool ConnectControlSocket();
    
    void OnConnect(AsyncSocket* socket);
    
    void OnHangingGetConnect(AsyncSocket* socket);
    
    void OnRead(AsyncSocket* socket);
    
    //有数据可以读取
    void OnHangingGetRead(AsyncSocket* socket);
    
    // Returns true if the whole response has been read.
    bool ReadIntoBuffer(AsyncSocket* socket, std::string* data,
                        size_t* content_length);
    
    void OnClose(AsyncSocket* socket, int err);
    
    void OnResolveResult(AsyncResolverInterface* resolver);
    
protected:
    PeerConnectionClientObserver*           _callback;
    rtc::SocketAddress                      _server_address;
    rtc::AsyncResolver*                     _resolver;
    rtc::scoped_ptr<rtc::AsyncSocket>       _control_socket;
    rtc::scoped_ptr<rtc::AsyncSocket>       _data_socket;
    
    std::string     _onconnect_data;
    std::string     _control_data;
    std::string     _notification_data;
    std::string     _client_name;
    Peers           _peers;
    State           _state;
    int             _my_id;
};

#endif /* defined(__webRTCAPP__rtpeerconnection__) */
