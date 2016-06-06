//
//  TcpListener.hpp
//  Vanilla
//
//  Created by ZengHongru on 16/6/5.
//
//

#ifndef TcpConnection_h
#define TcpConnection_h

#include "IOEvent.h"
#include "TcpSocket.h"

namespace vanilla {
    
class TcpConnection : public IOEvent {
public:
    virtual void canRead();
    virtual void canWrite();
private:
    std::shared_ptr<TcpSocket> socket_;
};
    
    
}



#endif /* TcpConnection_h */
