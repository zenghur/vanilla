// Copyright (c) 2016 zenghur

#ifndef NET_TCPCONNECTION_H_
#define NET_TCPCONNECTION_H_

#include "IOEvent.h"
#include "TcpSocket.h"
#include "Poller.h"
#include "SessionIDDispatcher.h"

namespace vanilla {
    
class Channel;
class Message;
  
class TcpConnection : public IOEvent {
 public:
   explicit TcpConnection(Poller *poller);
   void init(Channel *channel, int fd, SessionIDDispatcher::SessionType sessionID);
   int getConnectionFd();
   SessionIDDispatcher::SessionType getSessionID();
   void closeConnection();
   Poller *getPoller();
  
 public:
   virtual void canRead();
   virtual void canWrite();
   virtual void receiveMsg(Message &item);
   virtual void close(vanilla::SessionIDDispatcher::SessionType sessionID);
   void send(char *data, int len);
  
 private:
   Poller *poller_;
   Channel *channel_;
   std::shared_ptr<TcpSocket> socket_;
   SessionIDDispatcher::SessionType sessionID_;
};
    
}  // namespace vanilla

#endif  // NET_TCPCONNECTION_H_
