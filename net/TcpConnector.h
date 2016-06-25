// Copyright (c) 2016 zenghur

#ifndef NET_TCPCONNECTOR_H_
#define NET_TCPCONNECTOR_H_

#include "TcpSocket.h"
#include "IOEvent.h"
#include "SessionIDDispatcher.h"

namespace vanilla {
class Poller;
class TcpConnector : public IOEvent {
 public:
   explicit TcpConnector(Poller *poller);
   virtual void canRead();
   virtual void canWrite();
   virtual void receiveMsg(Message *item);
   virtual void close(vanilla::SessionIDDispatcher::SessionType sessionID);
   void connect(std::string peerName, uint16_t port);
   int getConnectorFd();
  
 private:
   TcpConnector(const TcpConnector &) = delete;
   TcpConnector& operator = (const TcpConnector&) = delete;
  
 private:
   Poller *poller_;
   Channel *channel_;
   SessionIDDispatcher::SessionType sessionID_;
   std::shared_ptr<TcpSocket> socket_;
};
  
}  // namespace vanilla

#endif  // NET_TCPCONNECTOR_H_
