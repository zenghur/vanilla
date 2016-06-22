// Copyright (c) 2016 zenghur

#include "SocketOption.h"

#include "Error.h"

using vanilla::SocketOption;

int SocketOption::setReuseAddr(int fd) {
  int optval = 1;
  int flag = setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));
  if (flag < 0) {
    printError();
  }
  return flag;
}

int SocketOption::setSndBuf(int fd, int size) {
  int flag = setsockopt(fd, SOL_SOCKET, SO_SNDBUF, &size, sizeof(size));
  if (flag < 0) {
    printError();
  }
  return flag;
}

int SocketOption::setRcvBuf(int fd, int size) {
  int flag = setsockopt(fd, SOL_SOCKET, SO_RCVBUF, &size, sizeof(size));
  if (flag < 0) {
    printError();
  }
  return flag;
}

int SocketOption::getSndBuf(int fd) {
  int optval;
  socklen_t len = sizeof(optval);
  int flag = getsockopt(fd, SOL_SOCKET, SO_SNDBUF, &optval, &len);
  if (flag < 0) {
    printError();
  }
  return optval;
}

int SocketOption::getRcvBuf(int fd) {
  int optval;
  socklen_t len = sizeof(optval);
  int flag = getsockopt(fd, SOL_SOCKET, SO_RCVBUF, &optval, &len);
  if (flag < 0) {
    printError();
  }
  return optval;
}

int SocketOption::setSndTimeO(int fd, struct timeval val) {
  int flag = setsockopt(fd, SOL_SOCKET, SO_SNDTIMEO, static_cast<const struct timeval *>(&val), sizeof(val));
  if (flag < 0) {
    printError();
  }
  return flag;
}

int SocketOption::setRcvTimeO(int fd, struct timeval val) {
  int flag = setsockopt(fd, SOL_SOCKET, SO_RCVTIMEO, static_cast<const struct timeval *>(&val), sizeof(val));
  if (flag < 0) {
    printError();
  }
  return flag;
}

struct timeval SocketOption::getSndTimeO(int fd) {
  struct timeval val;
  socklen_t len;
  int flag = getsockopt(fd, SOL_SOCKET, SO_SNDTIMEO, static_cast<struct timeval *>(&val), &len);
  if (flag < 0) {
    printError();
  }
  return val;
}

struct timeval SocketOption::getRcvTimeO(int fd) {
  struct timeval val;
  socklen_t len;
  int flag = getsockopt(fd, SOL_SOCKET, SO_RCVTIMEO, static_cast<struct timeval *>(&val), &len);
  if (flag < 0) {
    printError();
  }
  return val;
}



