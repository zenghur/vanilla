// Copyright (c) 2016 zenghur

#ifndef VANILLA_NET_POLLER_H_
#define VANILLA_NET_POLLER_H_

#include "Noncopyable.h"

#include <unistd.h>
#include <sys/types.h>

#include <memory>

namespace vanilla {
    

    
class Poller : private vanilla::Noncopyable {
public:
    typedef uint32_t PollerEventType;
    static std::unique_ptr<Poller> createPoller();
public:
    virtual void poll() = 0;
    virtual void init() = 0;
    virtual void addFd(int fd, PollerEventType mask, void *udata) = 0;
    virtual void deleteFd(int fd, PollerEventType mask) = 0;
    virtual void modFd(int fd, PollerEventType mask, void *udata) = 0;
    virtual ~Poller() {};
};
    
enum class PollerEvent: Poller::PollerEventType {
    POLLER_IN = 0x00000001, // readable
    POLLER_OUT = 0x00000010 // writable
};
    
}


    

#endif