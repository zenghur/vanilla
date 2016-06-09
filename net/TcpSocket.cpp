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
#include <sys/fcntl.h>
#include <netdb.h>

#include <iostream>
#include <sstream>
#include <cassert>
#include <err.h>


#include "TcpSocket.h"
#include "SocketOption.h"
#include "Error.h"
#include "Endian.h"

using namespace vanilla;

TcpSocket::TcpSocket(int fd): sockfd_(fd),
                              isNonBlocking_(false),
                              sendBuf_(SND_BUF),
                              sendBufStartIndex_(0),
                              sendLen_(0),
                              recvBuf_(RCV_BUF),
                              recvBufStartIndex_(0),
                              recvLen_(0)
{
   
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

void TcpSocket::setNonBlockStatus(bool flag)
{
    isNonBlocking_ = flag;
}

bool TcpSocket::getNonBlockStatus()
{
    return isNonBlocking_;
}

void TcpSocket::makeNonBlock(int fd)
{
    assert(fd >= 0);
    
    int flags = fcntl(fd, F_GETFL, 0);
    if (flags < 0) {
        printError();
    }
    
    flags = fcntl(fd, F_SETFL, flags | O_NONBLOCK);
    if (flags < 0) {
        printError();
    }
}

std::shared_ptr<TcpSocket> TcpSocket::createListener(std::string ip, uint16_t port)
{
    int fd = socket(PF_INET, SOCK_STREAM, 0);
    if (fd < 0) {
        printError();
    }
    
    SocketOption::setReuseAddr(fd);
    TcpSocket::makeNonBlock(fd);
    
    
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
    
    std::shared_ptr<TcpSocket> socket(new TcpSocket(fd));
    socket->setNonBlockStatus(true);
    
    return std::move(socket);
}

std::shared_ptr<TcpSocket> TcpSocket::createConnector(std::string peerName, uint16_t port)
{
    int fd = socket(PF_INET, SOCK_STREAM, 0);
    if (fd < 0) {
        printError();
    }
    
    makeNonBlock(fd);
    
        
    
    std::shared_ptr<TcpSocket> socket = std::make_shared<TcpSocket>(fd);
    socket->setNonBlockStatus(true);
    
    return socket;
}

int TcpSocket::nonBlockSend(char *data, size_t len)
{
    assert(isNonBlocking_);
    
    ssize_t nBytes = ::send(sockfd_, data, len, 0);
    
    // 3种情况
    if (nBytes == -1 && (errno == EWOULDBLOCK || errno == EAGAIN || errno == EINTR)) {
        return 0;
    }
    
    if (nBytes == -1) {
        return -1;
    }
    
    if (nBytes == 0) {
        return 0;
    }
    
    return static_cast<int>(nBytes);
}

int TcpSocket::nonBlockRecv(char *data, size_t len)
{
    assert(isNonBlocking_);

    ssize_t nBytes = ::recv(sockfd_, data, len, 0);
    
    if ((nBytes == -1) && (errno == EWOULDBLOCK || errno == EAGAIN || errno == EINTR)) {
        return 0;
    }
    
    if (nBytes == -1) {
        return -1;
    }
    
    if (nBytes == 0) {
        return 0;
    }
    
    return static_cast<int>(nBytes);
}

int TcpSocket::blockSend(char *data, size_t len)
{
    assert(!isNonBlocking_);
    
    ssize_t ret;
    
    while (len != 0 && (ret = ::send(sockfd_, data, len, 0)) != 0) {
        if (ret == -1 && errno == EINTR) {
            continue;
        }
        else {
            break;
        }
        data += ret;
        len -= ret;
    }
    return static_cast<int>(len);
}

int TcpSocket::blockRecv(char *data, size_t len)
{
    assert(!isNonBlocking_);
    
    ssize_t ret;

    while (len != 0 && (ret == ::recv(sockfd_, data, len, 0)) != 0) {
        if (ret == -1 && errno == EINTR) {
            continue;
        }
        else {
            break;
        }
        data += ret;
        len -= ret;
    }
    return static_cast<int>(len);
}

