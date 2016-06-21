// Copyright (c) 2016 zenghur

#ifndef NET_SOCKETOPTION_H_
#define NET_SOCKETOPTION_H_

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
}  // namespace vanilla

#endif  // NET_SOCKETOPTION_H_
