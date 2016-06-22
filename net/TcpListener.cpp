// Copyright (c) 2016 zenghur

#include "TcpListener.h"

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <iostream>
#include <cassert>

#include "Endian.h"
#include "Poller.h"
#include "TcpConnection.h"
#include "Error.h"

using vanilla::TcpListener;

int TcpListener::getListenerFd() {
  assert(socket_);
  return socket_->getSocketFd();
}

void TcpListener::listen(std::string ip, uint16_t port) {
  socket_ = TcpSocket::createListener(ip, port);
}

