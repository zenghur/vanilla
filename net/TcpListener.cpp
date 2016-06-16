//
//  TcpListener.cpp
//  Vanilla
//
//  Created by ZengHongru on 16/6/5.
//
//

#include "TcpListener.h"
#include "Error.h"

#include <sys/socket.h>
#include <netinet/in.h>
#include "Endian.h"
#include "Poller.h"
#include "TcpConnection.h"

#include <iostream>
#include <cassert>
#include <arpa/inet.h>

using namespace vanilla;
using namespace std;

TcpListener::TcpListener(Poller *poller): socket_(nullptr),
                                          poller_(poller)
{
    
}

int TcpListener::getListenerFd()
{
    return socket_->getSocketFd();
}

void TcpListener::listen(std::string ip, uint16_t port)
{
    assert(poller_);
    socket_ = TcpSocket::createListener(ip, port);
    poller_->addFd(getListenerFd(), static_cast<Poller::PollerEventType>(PollerEvent::POLLER_IN), this);
}

void TcpListener::canRead()
{
    do {
    
        struct sockaddr_in clientAddr;
        socklen_t len = sizeof(socklen_t);
        
        // non-blocking accept;
        int clientFd = ::accept(socket_->getSocketFd(), reinterpret_cast<struct sockaddr *>(&clientAddr), &len);
        
        if (clientFd < 0) {
            
            if (errno == EAGAIN || errno == EWOULDBLOCK)
                break;
            
            if (errno == EINTR) {
                continue;
            }
        }
        
        TcpConnection *connection = new TcpConnection(poller_);
        connection->init(clientFd);
        
        static int connections = 0;
        int port = be16toh(clientAddr.sin_port);
        string ip(inet_ntoa(clientAddr.sin_addr));
        
        std::cout << "connection socket: " <<  clientFd << " ip: " << ip  << " port: " << port << std::endl;
        std::cout << "当前连接数: " << ++connections << std::endl;
        
    } while (true);
    
}

