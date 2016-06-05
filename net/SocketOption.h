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

namespace vanilla {
    
class SocketOption {
public:
    static int setReuseAddr(int fd);
    static int setSndBuf(int fd, int size);
    static int setRcvBuf(int fd, int size);
public:
    static int getSndBuf(int fd);
    static int getRcvBuf(int fd);
};
    
    
}

#endif /* SocketOption_h */
