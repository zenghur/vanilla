// Copyright (c) 2016 zenghur

#ifndef NET_TCPCONNECTION_H_
#define NET_TCPCONNECTION_H_

#include "IOEvent.h"
#include "TcpSocket.h"
#include "Poller.h"

namespace vanilla {
    
class Channel;
class Message;
    
class TcpConnection : public IOEvent {
 public:
   explicit TcpConnection(Poller *poller);
   void init(Channel *channel, int fd, uint64_t sessionID);
   int getConnectionFd();
   uint64_t getSessionID();
   void closeConnection();
  
 public:
   virtual void canRead();
   virtual void canWrite();
   virtual void receiveMsg(Message *message);
   void send(char *data, int len);
  
 private:
   Poller *poller_;
   Channel *channel_;
   std::shared_ptr<TcpSocket> socket_;
   uint64_t sessionID_;
};
    
}  // namespace vanilla

#endif  // NET_TCPCONNECTION_H_
