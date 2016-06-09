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

#include <iostream>
#include <arpa/inet.h>

using namespace vanilla;
using namespace std;

TcpListener::TcpListener()
{
    
}

int TcpListener::getListenerFd()
{
    return socket_->getSocketFd();
}

void TcpListener::listen(std::string ip, uint16_t port)
{
    socket_ = TcpSocket::createListener(ip, port);
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
        
        static int connections = 0;
        int port = be16toh(clientAddr.sin_port);
        string ip(inet_ntoa(clientAddr.sin_addr));
        
    
        std::cout << "connection socket: " <<  clientFd << " ip: " << ip  << " port: " << port << std::endl;
        std::cout << "当前连接数: " << ++connections << std::endl;
        
    } while (true);
    
}

void TcpListener::canWrite()
{
    
}
