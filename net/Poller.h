#ifndef VANILLA_NET_POLLER_H_
#define VANILLA_NET_POLLER_H_

#include "Noncopyable.h"

#include <unistd.h>
// 分别封装kqueue和epoll


enum class POLLER_EVENT {
    ePOLLER_IN = 0x01,
    ePOLLER_OUT = 0x10,
};

class Poller {
public:
    virtual void poll() = 0;
    virtual void init() = 0;
    virtual void addFd(int fd, int mask, void *udata) = 0;
    virtual void deleteFd(int fd, int mask, void *udata) = 0;
    virtual void modFd(int fd, int mask, void *udata) = 0;
    virtual ~Poller() {};
};
    
#ifdef __APPLE__
#include <sys/event.h>

// kernel event queue
class Kqueue : public Poller, private vanilla::Noncopyable {
public:
    Kqueue();
    ~Kqueue();
public:
    virtual void init();
    virtual void addFd(int fd, int mask, void *udata);
    virtual void deleteFd(int fd, int mask, void *udata);
    virtual void modFd(int fd, int mask, void *udata);
    virtual void poll();
private:
    static struct timespec timeout;
    static const int MAX_EVENTS_ = 30;
    struct kevent events_[MAX_EVENTS_];
    int kqfd_;
};

#elif __linux__
    
class Epoll : public Poller, private vanilla::Noncopyable {
public:
    Epoll();
    ~Epoll();
public:
    virtual void init();
    virtual void addFd(int fd, POLLER_EVENT event, void *udata);
    virtual void deleteFd(int fd, POLLER_EVENT event, void *udata);
    virtual void modFd(int fd, POLLER_EVENT event, POLLER_OPERATION operation, void *udata);
    virtual void poll();
private:
    int epollfd_;
    const static int timeout = 1;
    struct epoll_event events_;
    static const int MAX_EVENTS = 30;
};
#endif
    



#endif