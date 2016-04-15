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

void Kqueue::addFd(int fd, int mask, void *udata)
{
    
}


void Kqueue::deleteFd(int fd, int mask, void *udata)
{
}

void Kqueue::modFd(int fd, int mask, void *udata)
{
}

void Kqueue::poll()
{

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
    
}

void Epoll::deleteFd(int fd, POLLER_EVENT event, void *udata)
{
    
}

void Epoll::modFd(int fd, POLLER_EVENT event, POLLER_OPERATION operation, void *udata)
{
    
}

void Epoll::poll()
{
    
}




#endif