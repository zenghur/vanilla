// Copyright (c) 2016 zenghur

#include "TcpSocket.h"

#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/fcntl.h>
#include <netdb.h>
#include <err.h>

#include <iostream>
#include <cassert>

#include "SocketOption.h"
#include "Error.h"
#include "Endian.h"
#include "IOEvent.h"
#include "MessageType.h"
#include "Message.h"
#include "TcpConnection.h"

using vanilla::TcpSocket;

TcpSocket::TcpSocket(int fd): connection_(nullptr),
                              sockfd_(fd),
                              isNonBlocking_(false),
                              sendBuf_(SND_BUF_SIZE),
                              sendBufStartIndex_(0),
                              sendLen_(0),
                              recvBuf_(RCV_BUF_SIZE),
                              recvLen_(0),
                              payLoadSize_(0) {
}

TcpSocket::~TcpSocket() {
  close();
}


void TcpSocket::close() {
  ::close(sockfd_);
  sockfd_ = -1;
  isNonBlocking_ = false;
  sendBufStartIndex_ = 0;
  sendLen_ = 0;
  recvLen_ = 0;
  payLoadSize_ = 0;
}

int TcpSocket::getSocketFd() {
  return sockfd_;
}

void TcpSocket::setConnection(TcpConnection *connection) {
  connection_ = connection;
}

void TcpSocket::setNonBlockStatus(bool flag) {
  isNonBlocking_ = flag;
}

bool TcpSocket::getNonBlockStatus() {
  return isNonBlocking_;
}

void TcpSocket::makeNonBlock(int fd) {
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

std::shared_ptr<TcpSocket> TcpSocket::createListener(std::string ip, uint16_t port) {
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
  } else if (flag == 0) {
    printError("IP地址不正确");
  }

  sockLen = sizeof(addr);

  if (bind(fd, reinterpret_cast<struct sockaddr *>(&addr), sockLen) < 0) {
    printError();
  }

  if (listen(fd, 64) < 0) {
    printError();
  }

  std::shared_ptr<TcpSocket> socket = std::make_shared<TcpSocket>(fd);
  socket->setNonBlockStatus(true);

  return std::move(socket);
}

std::shared_ptr<TcpSocket> TcpSocket::createConnector(std::string peerName, uint16_t port) {
  int fd = socket(PF_INET, SOCK_STREAM, 0);
  if (fd < 0) {
    printError();
  }

  makeNonBlock(fd);

  struct sockaddr_in peerAddr;
  memset(&peerAddr, 0, sizeof(peerAddr));
  peerAddr.sin_family = AF_INET;
  peerAddr.sin_port = htobe16(port);

  int flag = inet_pton(AF_INET, peerName.c_str(), &peerAddr.sin_addr.s_addr);
  if (flag == 0) {
    struct hostent *entry;
    entry = gethostbyname(peerName.c_str());
    if (entry) {
      memcpy(&peerAddr.sin_addr.s_addr, entry->h_addr_list[0], entry->h_length);
    }
  }

  bool isConnect = false;
  if (connect(fd, reinterpret_cast<struct sockaddr *>(&peerAddr), sizeof(peerAddr)) < 0) {
    ::close(fd);
    fd = -1;
  } else {
    isConnect = true;
  }
  std::shared_ptr<TcpSocket> socket = std::make_shared<TcpSocket>(fd);
  if (isConnect) {
    socket->setNonBlockStatus(true);
  }
  return socket;
}

int TcpSocket::nonBlockSend(char *data, size_t len) {
  assert(isNonBlocking_);

  ssize_t totalLen = len;
  if (len > 0) {
    ssize_t ret;
    
    while ((ret = ::send(sockfd_, data, len, 0)) != 0 && (len != 0)) {
      if (ret == -1 && (errno == EWOULDBLOCK || errno == EAGAIN)) {
        break;
      } else if (ret == -1 && errno == EINTR) {
        continue;
      } else if (ret == -1) {
        return -1;
      }
      
      data += ret;
      len -= ret;
    }
  }
  return totalLen - len;
}

int TcpSocket::nonBlockRecv(char *data, size_t len) {
  assert(isNonBlocking_);
  ssize_t totalLen = len;
  if (len > 0) {
      ssize_t ret;
      while ((ret = ::recv(sockfd_, data, len, 0)) != 0 && (len != 0)) {
        std::cout << ret << " : bytes" << std::endl;
        if (ret == -1 && (errno == EWOULDBLOCK || errno == EAGAIN)) {
          break;
        } else if (ret == -1 && errno == EINTR) {
          continue;
        } else if (ret == -1) {
          return -1;
        }
        len -= ret;
        data += ret;
      }
  }
  return totalLen - len;
}

int TcpSocket::blockSend(char *data, size_t len) {
  assert(!isNonBlocking_);

  ssize_t ret;
  ssize_t totalLen = len;

  while (len != 0 && (ret = ::send(sockfd_, data, len, 0)) != 0) {
    if (ret == -1 && errno == EINTR) {
      continue;
    } else if (ret == -1 && (errno == EWOULDBLOCK || errno == EAGAIN)) {  // 设置SO_RCVTIMEO 和 SO_SNDTIMEO 在阻塞模式下也可能发送eagain
      break;
    } else if (ret == -1) {
      return -1;
    }
    
    data += ret;
    len -= ret;
  }
  return totalLen - len;
}

int TcpSocket::blockRecv(char *data, size_t len) {
  assert(!isNonBlocking_);

  ssize_t ret;
  ssize_t totalLen = len;

  while (len != 0 && (ret = ::recv(sockfd_, data, len, 0)) != 0) {
    if (ret == -1 && errno == EINTR) {
      continue;
    } else if (ret == -1 && (errno == EWOULDBLOCK || errno == EAGAIN)) {
      break;
    } else if (ret == -1) {
      return -1;
    }
    data += ret;
    len -= ret;
  }
  return totalLen - len;
}

int TcpSocket::getSendLen() {
  return sendLen_;
}

int TcpSocket::send(char *data, int len) {
  int ret = 0;
  do {
      ret = sendBuf();
      
      if (ret == -1) {
        break;
      }
      
      if (sendLen_ > 0) {
        ret = putResponseDataInBuf(data, len);
        if (ret == -1) {
          break;
        }
      } else {
        ret = nonBlockSend(data, len);
        if (ret == -1) {
          break;
        }
        if (ret < len) {
          ret = putResponseDataInBuf(data + ret, len - ret);
          if (ret == -1) {
            break;
          }
        }
      }
  } while (false);
  if (sendLen_ > 0) {
     connection_->getPoller()->modFd(sockfd_, static_cast<Poller::PollerEventType>(PollerEvent::POLLER_IN) | static_cast<Poller::PollerEventType>(PollerEvent::POLLER_OUT), connection_);
  }
  return ret;
}

int TcpSocket::sendBuf() {
  while (sendLen_ > 0) {
    int bytesTobeSent = 0;
    if (sendBufStartIndex_ + sendLen_ > SND_BUF_SIZE) {
      bytesTobeSent = SND_BUF_SIZE - sendBufStartIndex_;
    } else {
      bytesTobeSent = sendLen_;
    }
    
    int actualBytesSent = nonBlockSend(&sendBuf_[sendBufStartIndex_], bytesTobeSent);
    if (actualBytesSent == -1) {
        return -1;
    }
    
    sendLen_ -= actualBytesSent;
    sendBufStartIndex_ = (sendBufStartIndex_ + actualBytesSent) % SND_BUF_SIZE;
    
    if (actualBytesSent < bytesTobeSent) {
      break;
    }
  }
  if (sendLen_ == 0) {
    connection_->getPoller()->modFd(sockfd_, static_cast<Poller::PollerEventType>(PollerEvent::POLLER_IN), connection_);
  }
  return 0;
}

int TcpSocket::putResponseDataInBuf(char *data, int len) {
  if (sendLen_ + len > SND_BUF_SIZE) {
    return -1;
  }

  int tailIndex = (sendBufStartIndex_ + sendLen_) % SND_BUF_SIZE;

  if (sendBufStartIndex_ < tailIndex) {
    std::copy(data, data + len, &sendBuf_[sendBufStartIndex_ + sendLen_]);
  } else {
    std::copy(data, data + len, &sendBuf_[tailIndex + 1]);
  }

  sendLen_ += len;

  return 0;
}

int TcpSocket::recv(IOEvent *event) {
  while (true) {
    int expectantBytes;
    if (payLoadSize_ == 0) {
      expectantBytes = RCV_HEADER_SIZE - recvLen_;
    } else {
      expectantBytes = RCV_HEADER_SIZE + payLoadSize_ - recvLen_;
    }
    
    int ret = nonBlockRecv(&recvBuf_[recvLen_], expectantBytes);
    if (ret == 0) {
      break;
    }
    
    if (ret == -1) {
      return -1;
    }
    
    recvLen_ += ret;
    
    if (ret < expectantBytes) {
      break;
    }
    
    if (payLoadSize_ == 0) {
      std::copy(&recvBuf_[0], &recvBuf_[RCV_HEADER_SIZE], &payLoadSize_);
      if (payLoadSize_ + RCV_HEADER_SIZE > RCV_BUF_SIZE || payLoadSize_ < 0) {
        return -1;
      }
    } else {
      Message item;
      item.type_ = NET_MSG;
      item.data_ = std::unique_ptr<char[]>(new char[payLoadSize_]);
      item.size_ = payLoadSize_;
      std::copy(&recvBuf_[RCV_HEADER_SIZE], &recvBuf_[RCV_HEADER_SIZE] + payLoadSize_, item.data_.get());
      if (event) {
        event->receiveMsg(&item);
      }
      recvLen_ = 0;
      payLoadSize_ = 0;
    }
  }
  return 0;
}


