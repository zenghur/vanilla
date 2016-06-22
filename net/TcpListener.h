// Copyright (c) 2016 zenghur

#ifndef NET_TCPLISTENER_H_
#define NET_TCPLISTENER_H_

#include "TcpSocket.h"

#include <string>

namespace vanilla {
    
class TcpListener {
 public:
   int getListenerFd();
   void listen(std::string ip, uint16_t port);
  
 private:
   std::shared_ptr<TcpSocket> socket_;
};
} // namespace vanilla

#endif  // NET_TCPLISTENER_H_

