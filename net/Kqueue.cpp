//
//  Kqueue.cpp
//  Vanilla
//
//  Created by ZengHongru on 16/4/15.
//
//

#include "Kqueue.h"
#include "Error.h"
#include "DateTime.h"
#include "IOEvent.h"
#include <iostream>

#include <unistd.h>
#include <time.h>

using namespace vanilla;
using namespace std;

#ifdef __APPLE__

Kqueue::Kqueue(): kqfd_(-1)
{
    events_.resize(MAX_EVENTS);
}

Kqueue::~Kqueue()
{
    if (kqfd_ >= 0) {
        close(kqfd_);
    }
}

void Kqueue::init()
{
    if ((kqfd_ = kqueue()) == -1) {
        printError();
    }
}

void Kqueue::addFd(int fd, int8_t mask, void *udata)
{
    struct kevent event;
    
    if (mask & static_cast<int8_t>(PollerEvent::POLLER_IN)) {
        EV_SET(&event, fd, EVFILT_READ, EV_ADD | EV_CLEAR, 0, 0, udata);
        if (kevent(kqfd_, &event, 1, NULL, 0, NULL) == -1) {
            printError();
        }
    }
    
    if (mask & static_cast<int8_t>(PollerEvent::POLLER_OUT) ) {
        EV_SET(&event, fd, EVFILT_WRITE, EV_ADD | EV_CLEAR, 0, 0, udata);
        if (kevent(kqfd_, &event, 1, NULL, 0, NULL) == -1) {
            printError();
        }
    }
}

void Kqueue::deleteFd(int fd, int8_t mask)
{
    struct kevent event;
    
    if (static_cast<int8_t>(mask) & static_cast<int8_t>(PollerEvent::POLLER_IN)) {
        EV_SET(&event, fd, EVFILT_READ, EV_DELETE, 0, 0, NULL);
        if (kevent(kqfd_, &event, 1, NULL, 0, NULL) == -1) {
            printError();
        }
    }
    
    if (static_cast<int8_t>(mask) & static_cast<int8_t>(PollerEvent::POLLER_OUT)) {
        EV_SET(&event, fd, EVFILT_WRITE, EV_DELETE, 0, 0, NULL);
        if (kevent(kqfd_, &event, 1, NULL, 0, NULL) == -1) {
            printError();
        }
    }
}

void Kqueue::modFd(int fd, int8_t mask, void *udata)
{
    struct kevent event;
    
    if (static_cast<int8_t>(mask) & static_cast<int8_t>(PollerEvent::POLLER_IN)) {
        EV_SET(&event, fd, EVFILT_READ, EV_ADD | EV_CLEAR, 0, 0, udata);
    }
    else {
        EV_SET(&event, fd, EVFILT_READ, EV_DELETE, 0, 0, udata);
    }
    
    if (kevent(kqfd_, &event, 1, NULL, 0, NULL) == -1) {
        printError();
    }
    
    if (static_cast<int8_t>(mask) & static_cast<int8_t>(PollerEvent::POLLER_OUT)) {
        EV_SET(&event, fd, EVFILT_WRITE, EV_ADD | EV_CLEAR, 0, 0, udata);
      
    }
    else {
        EV_SET(&event, fd, EVFILT_WRITE, EV_DELETE, 0, 0, udata);
    }
    
    if (kevent(kqfd_, &event, 1, NULL, 0, NULL) == -1) {
        printError();
    }
}

void Kqueue::poll()
{
    int n = 0;
    struct timespec spec = DateTime::msToTimespec(timeout);
    if ( (n = kevent(kqfd_, NULL, 0, &*events_.begin(), events_.size(), &spec)) == -1) {
        printError();
    }

    for (size_t index = 0; index < n; ++index) {
        
        IOEvent *io = reinterpret_cast<IOEvent*>(events_[index].udata);
        
        if (!io) {
            continue;
        }
        
        if ((events_[index].flags == EV_ERROR) || (events_[index].flags == EV_EOF)) {
            fprintf(stderr, "EV_ERROR: %s\n", strerror(events_[index].data));
            ::close(events_[index].ident);
            continue;
        }
        
        else if (events_[index].filter == EVFILT_READ) {
            io->canRead();
        }
        
        else if (events_[index].filter == EVFILT_WRITE) {
            io->canWrite();
        }
    }
}

#endif

