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
#include "Poller.h"

namespace vanilla {
    
class TcpConnection : public IOEvent {
public:
    explicit TcpConnection(Poller *poller);
    void init(int fd);
    int getConnectionFd();
public:
    virtual void canRead();
    virtual void canWrite();
    int send(char *data, int len);
private:
    Poller *poller_;
    std::shared_ptr<TcpSocket> socket_;
};
    
    
}



#endif /* TcpConnection_h */
