//
//  TcpConnector.hpp
//  Vanilla
//
//  Created by ZengHongru on 16/6/5.
//
//

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
    
    void connect(std::string peerName, uint16_t port);
    
    int getConnectorFd();
private:
    std::shared_ptr<TcpSocket> socket_;
};
    
    
}



#endif /* TcpConnector_h */
