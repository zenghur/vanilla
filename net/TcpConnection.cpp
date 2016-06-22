// Copyright (c) 2016 zenghur

#include "TcpConnection.h"

#include <cassert>

#include "TcpSocket.h"
#include "Channel.h"
#include "Poller.h"

using vanilla::TcpConnection;
using vanilla::SessionIDDispatcher;
using vanilla::Poller;

TcpConnection::TcpConnection(Poller *poller): socket_(nullptr),
                                              poller_(poller),
                                              channel_(nullptr),
                                              sessionID_(0) {
}

SessionIDDispatcher::SessionType TcpConnection::getSessionID() {
  return sessionID_;
}

int TcpConnection::getConnectionFd() {
  if (socket_) {
    return socket_->getSocketFd();
  } else {
    return -1;
  }
}

void TcpConnection::closeConnection() {
  socket_->close();
}

Poller *TcpConnection::getPoller() {
  return poller_;
}

void TcpConnection::init(Channel *channel, int fd, SessionIDDispatcher::SessionType sessionID) {
  assert(poller_);
  channel_ = channel;
  socket_  = std::make_shared<TcpSocket>(fd);
  TcpSocket::makeNonBlock(fd);
  socket_->setNonBlockStatus(true);
  socket_->setConnection(this);
  poller_->addFd(fd, static_cast<Poller::PollerEventType>(PollerEvent::POLLER_IN), this);
  sessionID_ = sessionID;
}


void TcpConnection::canRead() {
  int ret = socket_->recv(this);
  if (ret == -1) {
    closeConnection();
  }
}

void TcpConnection::canWrite() {
  int ret = socket_->sendBuf();
  if (ret == -1) {
    closeConnection();
  }
}

void TcpConnection::receiveMsg(Message *message) {
  message->sessionID_ = sessionID_;
  channel_->sendMessageToBoss(message);
}

void TcpConnection::send(char *data, int len) {
  int ret = socket_->send(data, len);
  if (ret == -1) {
    closeConnection();
  }
}
