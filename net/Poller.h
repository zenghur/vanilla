#ifndef VANILLA_NET_POLLER_H_
#define VANILLA_NET_POLLER_H_

#include "Noncopyable.h"

#include <unistd.h>
// 分别封装kqueue和epoll


enum class POLLER_EVENT {
    ePOLLER_IN,
    ePOLLER_OUT,
};
    
class Poller {
public:
    virtual void poll() = 0;
    virtual void addFd(int fd, POLLER_EVENT event, void *udata) = 0;
    virtual void deleteFd(int fd, POLLER_EVENT event, void *udata) = 0;
    virtual void modFd(int fd, POLLER_EVENT event, void *udata) = 0;
    virtual ~Poller() {};
};
    
#ifdef __APPLE__
#include <sys/event.h>

// kernel event queue
class Kqueue : public Poller, private vanilla::Noncopyable {
public:
    Kqueue();
    void  init();
    ~Kqueue();
public:
    virtual void addFd(int fd, POLLER_EVENT event, void *udata);
    virtual void deleteFd(int fd, POLLER_EVENT event, void *udata);
    virtual void modFd(int fd, POLLER_EVENT event, void *udata);
private:
    static struct timespec timeout;
    static const int MAX_EVENTS_ = 30;
    struct kevent events_[MAX_EVENTS_];
    int fd_;
};

#elif __linux__
    
class Epoll : public Poller, private vanilla::Noncopyable {
public:
private:
    int fd_;
};
#endif
    



#endif