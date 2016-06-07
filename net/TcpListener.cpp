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
        struct sockaddr_in addr;
        socklen_t len;
        int fd = ::accept(socket_->getSocketFd(), (struct sockaddr *)(&addr), &len);
        if (fd < 0) {
            if (errno == EAGAIN || errno == EWOULDBLOCK)
                break;
        }
        
        int port = be16toh(addr.sin_port);
        string ip(inet_ntoa(addr.sin_addr));
        
    
        std::cout << "connection socket: " <<  fd << " ip: " << ip  << " port: " << port << std::endl;
    } while (true);
    
}

void TcpListener::canWrite()
{
    
}
