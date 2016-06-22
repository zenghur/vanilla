// Copyright (c) 2016 zenghur

#ifndef NET_TCPSOCKET_H_
#define NET_TCPSOCKET_H_

#include <stdint.h>

#include <string>
#include <vector>

namespace vanilla {

class Channel;
class IOEvent;

class TcpSocket {
 public:
   static const int SND_BUF_SIZE = 64 * 1024;
   static const int RCV_BUF_SIZE = 64 * 1024;
   static const int RCV_HEADER_SIZE = 4;
  
 public:
   explicit TcpSocket(int fd = -1);
   ~TcpSocket();
   void close();

   int nonBlockSend(char *data, size_t len);
   int nonBlockRecv(char *data, size_t len);

   int blockSend(char *data, size_t len);
   int blockRecv(char *data, size_t len);

   int getSocketFd();

   static void makeNonBlock(int fd);
   void setNonBlockStatus(bool flag);
   bool getNonBlockStatus();
  
 public:
   // 发送相关
   int send(char *data, int len);
   int getSendLen();
   int sendBuf();
   int putResponseDataInBuf(char *data, int len);
  
 public:
   // 接收相关
   int recv(IOEvent *event);
  
 public:
   static std::shared_ptr<TcpSocket> createListener(std::string ip, uint16_t port);
   static std::shared_ptr<TcpSocket> createConnector(std::string peerName, uint16_t port);
    
 private:
   TcpSocket(const TcpSocket &) = delete;
   TcpSocket& operator = (const TcpSocket &) = delete;
    
 private:
   bool isNonBlocking_;
   int sockfd_;
  
   // ring buffer
   std::vector<char> sendBuf_;
   int sendBufStartIndex_;
   int sendLen_;
  
   // message buffer
   std::vector<char> recvBuf_;
   int recvLen_;
   int payLoadSize_;
};
    
}  // namespace vanilla

#endif  // NET_TCPSOCKET_H_