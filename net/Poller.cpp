#include "Poller.h"
#include "Error.hpp"

#include <sys/time.h>

using namespace vanilla;


#ifdef __APPLE__
#include <sys/event.h>

// kqueue(), kevent(), EV_SET
// kevent由tuple(ident, filter, udata标识)

struct timespec Kqueue::timeout = { 5, 0 }; // block


Kqueue::Kqueue() : fd_(-1)
{
    
}

void Kqueue::init()
{
    fd_ = kqueue();
    if (fd_ == -1) {
        printError();
    }
}

Kqueue::~Kqueue()
{
    if (fd_ >= 0) {
        if (close(fd_) == -1) {
            printError();
        }
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
    
    if (kevent(fd_, &ev, 1, NULL, 0, &timeout) == -1) {
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
    if (kevent(fd_, &ev, 1, NULL, 0, &timeout) == -1) {
        printError();
    }
}

void Kqueue::modFd(int fd, POLLER_EVENT event, void *udata)
{
   
}



#elif __linux__


#endif