// Copyright (c) 2016 zenghur

#include <cassert>

#include "TcpConnection.h"
#include "TcpSocket.h"
#include "Channel.h"

using vanilla::TcpConnection;


TcpConnection::TcpConnection(Poller *poller): socket_(nullptr),
                                              poller_(poller),
                                              channel_(nullptr),
                                              sessionID_(-1)
{
    
}

uint64_t TcpConnection::getSessionID()
{
    return sessionID_;
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

void TcpConnection::init(Channel *channel, int fd, uint64_t sessionID)
{
    assert(poller_);
    channel_ = channel;
    
    socket_  = std::make_shared<TcpSocket>(fd);
    TcpSocket::makeNonBlock(fd);
    socket_->setNonBlockStatus(true);
    
    poller_->addFd(fd, static_cast<Poller::PollerEventType>(PollerEvent::POLLER_IN) | static_cast<Poller::PollerEventType>(PollerEvent::POLLER_OUT), this);
    sessionID_ = sessionID;
}


void TcpConnection::canRead()
{
    int ret = socket_->recv(this);
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

void TcpConnection::receiveMsg(Message *message)
{
    message->sessionID_ = sessionID_;
    channel_->sendMessageToBoss(message);
}

void TcpConnection::send(char *data, int len)
{
    int ret = socket_->send(data, len);
    if (ret == -1) {
        closeConnection();
    }
}
