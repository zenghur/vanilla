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
    if (socket_) {
        return socket_->getSocketFd();
    }
    else {
        return -1;
    }
}

void TcpConnection::closeConnection()
{
    socket_->close();
}

void TcpConnection::init(int fd)
{
    assert(poller_);
    
    socket_  = std::make_shared<TcpSocket>(fd);
    TcpSocket::makeNonBlock(fd);
    socket_->setNonBlockStatus(true);
    
    poller_->addFd(fd, static_cast<Poller::PollerEventType>(PollerEvent::POLLER_IN) | static_cast<Poller::PollerEventType>(PollerEvent::POLLER_OUT), this);
    
}


void TcpConnection::canRead()
{
    int ret = socket_->recv();
    if (ret == -1) {
        closeConnection();
    }
}

void TcpConnection::canWrite()
{
    int ret = socket_->sendBuf();
    if (ret == -1) {
        closeConnection();
    }
}

void TcpConnection::send(char *data, int len)
{
    int ret = socket_->send(data, len);
    if (ret == -1) {
        closeConnection();
    }
}
