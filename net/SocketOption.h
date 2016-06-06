//
//  SocketOption.hpp
//  Vanilla
//
//  Created by ZengHongru on 16/6/5.
//
//

#ifndef SocketOption_h
#define SocketOption_h

#include <sys/socket.h>
#include <sys/time.h>

namespace vanilla {
    
class SocketOption {
public:
    static int setReuseAddr(int fd);
    static int setSndBuf(int fd, int size);
    static int setRcvBuf(int fd, int size);
    static int setSndTimeO(int fd, struct timeval val);
    static int setRcvTimeO(int fd, struct timeval val);
public:
    static int getSndBuf(int fd);
    static int getRcvBuf(int fd);
    static struct timeval getSndTimeO(int fd);
    static struct timeval getRcvTimeO(int fd);
};
    
    
}

#endif /* SocketOption_h */
