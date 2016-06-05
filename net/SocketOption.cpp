//
//  SocketOption.cpp
//  Vanilla
//
//  Created by ZengHongru on 16/6/5.
//
//

#include "SocketOption.h"
#include "Error.h"

using namespace vanilla;

int SocketOption::setReuseAddr(int fd)
{
    int optval = 1;
    int flag = setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));
    if (flag < 0) {
        printError();
    }
    return flag;
}

int SocketOption::setSndBuf(int fd, int size)
{
    int flag = setsockopt(fd, SOL_SOCKET, SO_SNDBUF, &size, sizeof(size));
    if (flag < 0) {
        printError();
    }
    return flag;
}

int SocketOption::setRcvBuf(int fd, int size)
{
    int flag = setsockopt(fd, SOL_SOCKET, SO_RCVBUF, &size, sizeof(size));
    if (flag < 0) {
        printError();
    }
    return flag;
}

int SocketOption::getSndBuf(int fd)
{
    int optval;
    socklen_t len = sizeof(optval);
    int flag = getsockopt(fd, SOL_SOCKET, SO_SNDBUF, &optval, &len);
    if (flag < 0) {
        printError();
    }
    return optval;
}

int SocketOption::getRcvBuf(int fd)
{
    int optval;
    socklen_t len = sizeof(optval);
    int flag = getsockopt(fd, SOL_SOCKET, SO_RCVBUF, &optval, &len);
    if (flag < 0) {
        printError();
    }
    return optval;
}
