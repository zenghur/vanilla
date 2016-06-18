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

TcpListener::TcpListener(Poller *poller): socket_(nullptr)
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

