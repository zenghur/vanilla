//
//  TcpListener.cpp
//  Vanilla
//
//  Created by ZengHongru on 16/6/5.
//
//

#include "TcpListener.h"

using namespace vanilla;

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
    
}

void TcpListener::canWrite()
{
    
}
