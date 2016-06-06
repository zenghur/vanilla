//
//  TcpListener.hpp
//  Vanilla
//
//  Created by ZengHongru on 16/6/5.
//
//

#ifndef TcpListener_h
#define TcpListener_h

#include "Noncopyable.h"
#include "TcpSocket.h"
#include "IOEvent.h"

#include <string>

namespace vanilla {

class TcpListener : public IOEvent {
public:
    TcpListener();
    int getListenerFd();
    void listen(std::string ip, uint16_t port);
public:
    virtual void canRead();
    virtual void canWrite();
private:
    std::shared_ptr<TcpSocket> socket_;
};
    
    
}

#endif /* TcpListener_h */
