#ifndef VANILLA_NET_POLLER_H_
#define VANILLA_NET_POLLER_H_

#include "Noncopyable.h"

#include <unistd.h>
#include <sys/types.h>

#include <memory>

namespace vanilla {
    
enum class PollerEvent: int8_t {
    POLLER_IN = 0x01,
    POLLER_OUT = 0x10
};
    
class Poller : private vanilla::Noncopyable {
public:
    static std::unique_ptr<Poller> createPoller();
public:
    virtual void poll() = 0;
    virtual void init() = 0;
    virtual void addFd(int fd, int mask, void *udata) = 0;
    virtual void deleteFd(int fd, int mask) = 0;
    virtual void modFd(int fd, int mask, void *udata) = 0;
    virtual ~Poller() {};
};
    
}


    

#endif