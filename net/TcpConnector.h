// Copyright (c) 2016 zenghur

#ifndef NET_TCPCONNECTOR_H_
#define NET_TCPCONNECTOR_H_

#include "TcpSocket.h"
#include "IOEvent.h"

namespace vanilla {
    
class TcpConnector : public IOEvent {
 public:
    virtual void canRead();
    virtual void canWrite();
    virtual void receiveMsg();
    void connect(std::string peerName, uint16_t port);
    int getConnectorFd();
    
 private:
    TcpConnector(const TcpConnector &) = delete;
    TcpConnector& operator = (const TcpConnector&) = delete;
    
 private:
    std::shared_ptr<TcpSocket> socket_;
};
  
}  // namespace vanilla

#endif  // NET_TCPCONNECTOR_H_
