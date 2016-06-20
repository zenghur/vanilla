// Copyright (c) 2016 zenghur

#ifndef TcpConnector_h
#define TcpConnector_h

#include "Noncopyable.h"
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
    std::shared_ptr<TcpSocket> socket_;
};
    
    
}



#endif /* TcpConnector_h */
