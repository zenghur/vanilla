// Copyright (c) 2016 zenghur

#include "TcpConnector.h"

#include <cassert>

#include "Poller.h"

using vanilla::TcpConnector;
using vanilla::Poller;


TcpConnector::TcpConnector(Poller *poller) : poller_(poller),
                                             channel_(nullptr),
                                             sessionID_(-1),
                                             socket_(nullptr) {
}

void TcpConnector::canRead() {
}

void TcpConnector::canWrite() {
}

void TcpConnector::receiveMsg(Message *message) {
}

void TcpConnector::connect(std::string peerName, uint16_t port) {
  assert(poller_);
  socket_ = TcpSocket::createConnector(peerName, port);
}


int TcpConnector::getConnectorFd() {
  return socket_->getSocketFd();
}

