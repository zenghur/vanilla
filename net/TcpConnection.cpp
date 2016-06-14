//
//  TcpListener.cpp
//  Vanilla
//
//  Created by ZengHongru on 16/6/5.
//
//

#include <cassert>

#include "TcpConnection.h"
#include "TcpSocket.h"

using namespace vanilla;


TcpConnection::TcpConnection(Poller *poller): socket_(nullptr),
                                              poller_(poller)
{
    
}

int TcpConnection::getConnectionFd()
{
    return socket_->getSocketFd();
}

void TcpConnection::init(int fd)
{
    assert(poller_);
    
    socket_  = std::make_shared<TcpSocket>(fd);
    TcpSocket::makeNonBlock(fd);
    poller_->addFd(fd, static_cast<int8_t>(PollerEvent::POLLER_IN), this);
    
}


void TcpConnection::canRead()
{
    
}

void TcpConnection::canWrite()
{
    
}

int TcpConnection::send(char *data, int len)
{
    
}
