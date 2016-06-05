//
//  Epoll.h
//  Vanilla
//
//  Created by ZengHongru on 16/4/15.
//
//

#ifndef __Vanilla__Epoll__
#define __Vanilla__Epoll__

#ifdef __linux__
#include <sys/epoll.h>

class Epoll : public Poller {
public:
    Epoll();
    virtual ~Epoll();
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


#endif /* defined(__Vanilla__Epoll__) */
