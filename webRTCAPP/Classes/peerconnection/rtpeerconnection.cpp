//
//  rtpeerconnection.cpp
//  webRTCAPP
//
//  Created by raymon_wang on 14-7-23.
//  Copyright (c) 2014年 yunwei. All rights reserved.
//

#include "rtpeerconnection.h"
#include "../webrtc/base/common.h"
#include "../webrtc/base/logging.h"
#include "../webrtc/base/socketfactory.h"
#include "../webrtc/base/stringutils.h"

#define kDefaultServerPort  8080;

AsyncSocket* CreateClientSocket(int family) {
    Thread* thread = Thread::Current();
    ASSERT(thread != NULL);
    return thread->socketserver()->CreateAsyncSocket(family, SOCK_DGRAM);
}

RtpPeerConnection::RtpPeerConnection() :
_callback(NULL),
_resolver(NULL),
_state(NOT_CONNECTED),
_my_id(-1)
{
    
}

RtpPeerConnection::~RtpPeerConnection()
{
    
}

int RtpPeerConnection::id() const {
    return _my_id;
}

bool RtpPeerConnection::is_connected() const {
    return _my_id != -1;
}

const RtpPeerConnection::Peers& RtpPeerConnection::peers() const {
    return _peers;
}

void RtpPeerConnection::RegisterObserver(PeerConnectionClientObserver *callback)
{
    _callback = callback;
}

void RtpPeerConnection::Connect(const std::string &server, int port, const std::string &client_name)
{
    if (_state != NOT_CONNECTED) {
        LOG(WARNING)
        << "The client must not be connected before you can call Connect()";
        _callback->OnServerConnectionFailure();
        return;
    }
    
    if (server.empty() || client_name.empty()) {
        _callback->OnServerConnectionFailure();
        return;
    }
    
    if (port <= 0)
        port = kDefaultServerPort;
    
    _server_address.SetIP(server);
    _server_address.SetPort(port);
    _client_name = client_name;
    
    if (_server_address.IsUnresolved()) {
        _state = RESOLVING;
        _resolver = new rtc::AsyncResolver();
        _resolver->SignalDone.connect(this, &RtpPeerConnection::OnResolveResult);
        _resolver->Start(_server_address);
    } else {
        DoConnect();
    }
}

bool RtpPeerConnection::IsSendingMessage() {
    return _state == CONNECTED && _control_socket->GetState() != Socket::CS_CLOSED;
}

#pragma protectedFunc
void RtpPeerConnection::DoConnect()
{
//    _control_socket.reset(CreateClientSocket(_server_address.ipaddr().family()));
    _data_socket.reset(CreateClientSocket(_server_address.ipaddr().family()));
    InitSocketSignals();
    char buffer[1024];
    sprintfn(buffer, sizeof(buffer),
             "GET /sign_in?%s HTTP/1.0\r\n\r\n", _client_name.c_str());
    _onconnect_data = buffer;
    
    bool ret = ConnectControlSocket();
    if (ret)
        _state = SIGNING_IN;
    if (!ret) {
        _callback->OnServerConnectionFailure();
    }
}

void RtpPeerConnection::Close() {
    _control_socket->Close();
    _data_socket->Close();
    _onconnect_data.clear();
    _peers.clear();
    if (_resolver != NULL) {
        _resolver->Destroy(false);
        _resolver = NULL;
    }
    _my_id = -1;
    _state = NOT_CONNECTED;
}


bool RtpPeerConnection::ConnectControlSocket() {
    ASSERT(control_socket_->GetState() == talk_base::Socket::CS_CLOSED);
    int err = _control_socket->Connect(_server_address);
    if (err == SOCKET_ERROR) {
        Close();
        return false;
    }
    return true;
}

void RtpPeerConnection::InitSocketSignals() {
    ASSERT(control_socket_.get() != NULL);
    ASSERT(hanging_get_.get() != NULL);
//    _control_socket->SignalCloseEvent.connect(this, &RtpPeerConnection::OnClose);
    _data_socket->SignalCloseEvent.connect(this, &RtpPeerConnection::OnClose);
//    _control_socket->SignalConnectEvent.connect(this, &RtpPeerConnection::OnConnect);
    _data_socket->SignalConnectEvent.connect(this, &RtpPeerConnection::OnHangingGetConnect);
//    _control_socket->SignalReadEvent.connect(this, &RtpPeerConnection::OnRead);
    _data_socket->SignalReadEvent.connect(this, &RtpPeerConnection::OnHangingGetRead);
}

void RtpPeerConnection::OnResolveResult(AsyncResolverInterface* resolver)
{
    if (resolver->GetError() != 0) {
        _callback->OnServerConnectionFailure();
        resolver->Destroy(false);
        resolver = NULL;
        _state = NOT_CONNECTED;
    } else {
        _server_address = resolver->address();
        DoConnect();
    }
}

//有数据可以读取
void RtpPeerConnection::OnHangingGetRead(AsyncSocket* socket)
{
    LOG(INFO) << __FUNCTION__;
    size_t content_length = 0;
    ReadIntoBuffer(socket, &_notification_data, &content_length);
    _notification_data.clear();
    
//    if (ReadIntoBuffer(socket, &_notification_data, &content_length)) {
//        size_t peer_id = 0, eoh = 0;
//        bool ok = ParseServerResponse(notification_data_, content_length,
//                                      &peer_id, &eoh);
//        
//        if (ok) {
//            // Store the position where the body begins.
//            size_t pos = eoh + 4;
//            
//            if (_my_id == static_cast<int>(peer_id)) {
//                // A notification about a new member or a member that just
//                // disconnected.
//                int id = 0;
//                std::string name;
//                bool connected = false;
//                if (ParseEntry(_notification_data.substr(pos), &name, &id,
//                               &connected)) {
//                    if (connected) {
//                        _peers[id] = name;
//                        _callback->OnPeerConnected(id, name);
//                    } else {
//                        _peers.erase(id);
//                        _callback->OnPeerDisconnected(id);
//                    }
//                }
//            } else {
//                OnMessageFromPeer(static_cast<int>(peer_id),
//                                  _notification_data.substr(pos));
//            }
//        }
//        
//        _notification_data.clear();
//    }
//    
//    if (_data_socket->GetState() == Socket::CS_CLOSED && _state == CONNECTED) {
//        _data_socket->Connect(_server_address);
//    }
}

// Returns true if the whole response has been read.
bool RtpPeerConnection::ReadIntoBuffer(AsyncSocket* socket, std::string* data,
                    size_t* content_length)
{
    char buffer[0xffff];
    do {
        int bytes = socket->Recv(buffer, sizeof(buffer));
        if (bytes <= 0)
            break;
        data->append(buffer, bytes);
    } while (true);
    
    bool ret = true;
//    bool ret = false;
//    size_t i = data->find("\r\n\r\n");
//    if (i != std::string::npos) {
//        LOG(INFO) << "Headers received";
//        if (GetHeaderValue(*data, i, "\r\nContent-Length: ", content_length)) {
//            size_t total_response_size = (i + 4) + *content_length;
//            if (data->length() >= total_response_size) {
//                ret = true;
//                std::string should_close;
//                const char kConnection[] = "\r\nConnection: ";
//                if (GetHeaderValue(*data, i, kConnection, &should_close) &&
//                    should_close.compare("close") == 0) {
//                    socket->Close();
//                    // Since we closed the socket, there was no notification delivered
//                    // to us.  Compensate by letting ourselves know.
//                    OnClose(socket, 0);
//                }
//            } else {
//                // We haven't received everything.  Just continue to accept data.
//            }
//        } else {
//            LOG(LS_ERROR) << "No content length field specified by the server.";
//        }
//    }
    return ret;

}





