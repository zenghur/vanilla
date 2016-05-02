//
//  Kqueue.h
//  Vanilla
//
//  Created by ZengHongru on 16/4/15.
//
//

#ifndef __Vanilla__Kqueue__
#define __Vanilla__Kqueue__

#include "Poller.h"

#include <vector>

#ifdef __APPLE__
#include <sys/event.h>

// kernel event queue
class Kqueue : public vanilla::Poller {
public:
    Kqueue();
    virtual ~Kqueue();
public:
    virtual void init();
    virtual void addFd(int fd, int mask, void *udata);
    virtual void deleteFd(int fd, int mask);
    virtual void modFd(int fd, int mask, void *udata);
    virtual void poll();
private:
    static const int timeout = 10; // milliseconds
    static const int MAX_EVENTS = 30;
    std::vector<struct kevent> events;
    int kqfd_;
};


#endif


#endif /* defined(__Vanilla__Kqueue__) */
