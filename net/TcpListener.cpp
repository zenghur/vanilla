// Copyright (c) 2016 zenghur

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


int TcpListener::getListenerFd()
{
    assert(socket_);
    return socket_->getSocketFd();
}

void TcpListener::listen(std::string ip, uint16_t port)
{
    socket_ = TcpSocket::createListener(ip, port);
}

