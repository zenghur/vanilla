//
//  Socket.cpp
//  Vanilla
//
//  Created by ZengHongru on 16/6/5.
//
//

#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <iostream>

#include "TcpSocket.h"
#include "SocketOption.h"
#include "Error.h"
#include "Endian.h"

using namespace vanilla;

TcpSocket::TcpSocket(int fd)
{
    sockfd_ = fd;
}

TcpSocket::~TcpSocket()
{
    close();
}


void TcpSocket::close()
{
    ::close(sockfd_);
}

int TcpSocket::getSocketFd()
{
    return sockfd_;
}

int TcpSocket::createListener(std::string ip, uint16_t port)
{
    int fd = socket(PF_INET, SOCK_STREAM, 0);
    if (fd < 0) {
        printError();
    }
    
    SocketOption::setReuseAddr(fd);
    
    struct sockaddr_in addr;
    socklen_t sockLen;
    
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htobe16(port);
    
    int flag = inet_pton(AF_INET, ip.c_str(), &addr.sin_addr.s_addr);
    if (flag == -1) {
        printError();
    }
    else if (flag == 0) {
        printError("IP地址不正确");
    }
    
    sockLen = sizeof(addr);
    
    if (bind(fd, reinterpret_cast<struct sockaddr *>(&addr), sockLen) < 0) {
        printError();
    }
    
    if (listen(fd, 64) < 0) {
        printError();
    }
    
    return fd;
}

int TcpSocket::createConnector(std::string ip, uint16_t port)
{
    int fd = socket(PF_INET, SOCK_STREAM, 0);
    if (fd < 0) {
        printError();
    }
    
    return fd;
}

