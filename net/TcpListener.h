// Copyright (c) 2016 zenghur

#ifndef TcpListener_h
#define TcpListener_h

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
    
    
}

#endif /* TcpListener_h */
