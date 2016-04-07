#ifndef VANILLA_NET_POLLER_H_
#define VANILLA_NET_POLLER_H_

#include "Noncopyable.h"

#include <unistd.h>
// 分别封装kqueue和epoll

namespace vanilla {
    
enum class POLLER_EVENT {
    eIn,
    eOut
};
    
class Poller {
public:
    virtual void poll() = 0;
    virtual void registerFd(int fd, POLLER_EVENT event, void *udata) = 0;
    virtual void unRegisterFd(int fd, POLLER_EVENT event, void *udata) = 0;
    virtual ~Poller() {};
};
    
#ifdef __APPLE__
#include <sys/event.h>
    
class Kqueue : public Poller, private vanilla::Noncopyable {
public:
    Kqueue();
    bool  init();
    ~Kqueue();
public:
    virtual void registerFd(int fd, POLLER_EVENT event, void *udata);
    virtual void unRegisterFd(int fd, POLLER_EVENT event, void *udata);
private:
    static const int MAX_EVENTS_ = 30;
    struct kevent events_[MAX_EVENTS_];
    int fd_;
};

#elif __linux__
    
class Epoll : public Poller, private vanilla::Noncopyable {
public:
private:
    int fd;
};
#endif
    
}


#endif