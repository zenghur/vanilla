// Copyright (c) 2016 zenghur

#include "TcpConnector.h"

using vanilla::TcpConnector;

void TcpConnector::canRead() {
}

void TcpConnector::canWrite() {
}

void TcpConnector::receiveMsg() {
}

void TcpConnector::connect(std::string peerName, uint16_t port) {
}


int TcpConnector::getConnectorFd() {
    return socket_->getSocketFd();
}

