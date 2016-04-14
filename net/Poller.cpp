#include "Poller.h"
#include "Error.hpp"

#include <sys/time.h>

#include <iostream>
#include <memory>

using namespace vanilla;
using namespace std;


#ifdef __APPLE__
#include <sys/event.h>

// kqueue(), kevent(), EV_SET，kevent
// kevent由tuple(ident, filter, udata标识)

struct timespec Kqueue::timeout = { 5, 0 }; // block

std::unique_ptr<Poller> createPoller()
{
    std::unique_ptr<Poller> p(new Kqueue());
    p->init();
    return std::move(p);
}

Kqueue::Kqueue() : kqfd_(-1)
{
    
}

void Kqueue::init()
{
    if ((kqfd_ = kqueue()) == -1) {
        printError();
    }
}

Kqueue::~Kqueue()
{
    if (kqfd_ >= 0) {
        close(kqfd_);
    }
}

void Kqueue::addFd(int fd, POLLER_EVENT event, void *udata)
{
    struct kevent ev;
    if (event == POLLER_EVENT::ePOLLER_IN) {
        EV_SET(&ev, fd, EVFILT_READ, EV_ADD, 0, 0, udata);
    }
    else if (event == POLLER_EVENT::ePOLLER_OUT) {
        EV_SET(&ev, fd, EVFILT_WRITE, EV_ADD, 0, 0, udata);
    }
    
    if (kevent(kqfd_, &ev, 1, NULL, 0, &timeout) == -1) {
        printError();
    }
    
}

void Kqueue::deleteFd(int fd, POLLER_EVENT event, void *udata)
{
    struct kevent ev;
    if (event == POLLER_EVENT::ePOLLER_IN) {
        EV_SET(&ev, fd, EVFILT_READ, EV_DELETE, 0, 0, udata);
    }
    else if (event == POLLER_EVENT::ePOLLER_OUT) {
        EV_SET(&ev, fd, EVFILT_WRITE, EV_DELETE, 0, 0, udata);
    }
    if (kevent(kqfd_, &ev, 1, NULL, 0, &timeout) == -1) {
        printError();
    }
}

void Kqueue::modFd(int fd, POLLER_EVENT event, POLLER_OPERATION operation, void *udata)
{
    struct kevent ev;
    
    if (event == POLLER_EVENT::ePOLLER_IN && operation == POLLER_OPERATION::ePOLLER_ADD) {
        EV_SET(&ev, fd, EVFILT_READ, EV_ADD, 0, 0, udata);
    }
    else if (event == POLLER_EVENT::ePOLLER_IN && operation == POLLER_OPERATION::ePOLLER_DELETE) {
        EV_SET(&ev, fd, EVFILT_READ, EV_DELETE, 0, 0, udata);
    }
    else if (event == POLLER_EVENT::ePOLLER_OUT && operation == POLLER_OPERATION::ePOLLER_ADD) {
        EV_SET(&ev, fd, EVFILT_WRITE, EV_ADD, 0, 0, udata);
    }
    else if (event == POLLER_EVENT::ePOLLER_OUT && operation == POLLER_OPERATION::ePOLLER_DELETE) {
        EV_SET(&ev, fd, EVFILT_WRITE, EV_DELETE, 0, 0, udata);
    }
    
    if (kevent(kqfd_, &ev, 1, NULL, 0, &timeout) == -1) {
        printError();
    }
}

void Kqueue::poll()
{
    int n = 0;
    if ( (n = kevent(kqfd_, NULL, 0, events_, MAX_EVENTS_, &timeout)) == -1) {
        printError();
    }
    for (size_t index = 0; index < n; ++index) {
        if (events_[index].filter == EVFILT_READ) {
            
        }
        else if (events_[index].filter == EVFILT_WRITE) {
            
        }
    }
}

#elif __linux__
#include <sys/epoll.h>

// epoll_create, epoll_ctl, epoll_wait
// struct epoll_event

std::unique_ptr<Poller> createPoller()
{
    std::unique_ptr<Poller> p(new Epoll());
    p->init();
    return std::move(p);
}

Epoll::Epoll(): epfd_(-1)
{
    
}

Epoll::~Epoll()
{
    if (epollfd_) {
        close(epollfd_);
    }
}

void Epoll::init()
{
    if ((epollfd_ = epoll_create(1)) == -1) {
        printError();
    }
}

void Epoll::addFd(int fd, POLLER_EVENT event, void *udata)
{
    struct epoll_event ev;
    ev.data.fd = fd;
    ev.data.ptr = udata;
    
    if (event == POLLER_EVENT::ePOLLER_IN) {
        ev.events = EPOLLIN;
        if (epoll_ctl(epollfd_, EPOLL_CTL_ADD, fd, &ev) == -1) {
            printError();
        }
    }
    else if (event == POLLER_EVENT::ePOLLER_OUT) {
        ev.events = EPOLLOUT;
        if (epoll_ctl(epollfd_, EPOLL_CTL_ADD, fd, &ev) == -1) {
            printError();
        }
    }
}

void Epoll::deleteFd(int fd, POLLER_EVENT event, void *udata)
{
    struct epoll_event ev;
    ev.data.fd = fd;
    ev.data.ptr = udata;
    
    if (event == POLLER_EVENT::ePOLLER_IN) {
        ev.events = EPOLLIN;
        if (epoll_ctl(epollfd_, EPOLL_CTL_DEL, fd, &ev) == -1) {
            printError();
        }
    }
    else if (event == POLLER_EVENT::ePOLLER_OUT) {
        ev.events = EPOLLOUT;
        if (epoll_ctl(epollfd_, EPOLL_CTL_DEL, fd, &ev) == -1) {
            printError();
        }
    }
}

void Epoll::modFd(int fd, POLLER_EVENT event, POLLER_OPERATION operation, void *udata)
{
    struct epoll_event ev;
    ev.data.fd = fd;
    
    if (event == POLLER_EVENT::ePOLLER_IN && operation == POLLER_OPERATION::ePOLLER_ADD) {
        ev.events = EPOLLIN;
        if (epoll_ctl(epollfd_, EPOLL_CTL_ADD, fd, &ev) == -1) {
            printError();
        }
    }
    else if (event == POLLER_EVENT::ePOLLER_IN && operation == POLLER_OPERATION::ePOLLER_DELETE) {
        ev.events = EPOLLIN;
        if (epoll_ctl(epollfd_, EPOLL_CTL_DEL, fd, &ev) == -1) {
            printError();
        }
    }
    else if (event == POLLER_EVENT::ePOLLER_OUT && operation == POLLER_OPERATION::ePOLLER_ADD) {
        ev.events = EPOLLOUT;
        if (epoll_ctl(epollfd_, EPOLL_CTL_ADD, fd, &ev) == -1) {
            printError();
        }
    }
    else if (event == POLLER_EVENT::ePOLLER_OUT && operation == POLLER_OPERATION::ePOLLER_DELETE) {
        ev.events = EPOLLOUT;
        if (epoll_ctl(epollfd_, EPOLL_CTL_DEL, fd, &ev) == -1) {
            printError();
        }
    }
}

void Epoll::poll()
{
    int n = 0;
    if ((n = epoll_wait(epollfd_, events, MAX_EVENTS_, timeout)) == -1) {
        printError();
    }
    for (size_t index = 0; index < n; ++index) {
        
    }
}




#endif