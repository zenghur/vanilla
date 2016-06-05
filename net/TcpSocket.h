//
//  Socket.hpp
//  Vanilla
//
//  Created by ZengHongru on 16/6/5.
//
//

#ifndef Socket_h
#define Socket_h

#include <stdint.h>

#include <string>

#include "Noncopyable.h"

namespace vanilla {

class TcpSocket : private vanilla::Noncopyable {
public:
    explicit TcpSocket(int fd = -1);
    ~TcpSocket();
    void close();
    
    int getSocketFd();
public:
    static int createListener(std::string ip, uint16_t port);
    static int createConnector(std::string ip, uint16_t port);
private:
    int sockfd_;
};
    
}

#endif /* Socket_h */
