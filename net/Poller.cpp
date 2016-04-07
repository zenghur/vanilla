#include "Poller.h"

using namespace vanilla;


#ifdef __APPLE__

Kqueue::Kqueue() : fd_(-1)
{
    
}

bool Kqueue::init()
{
    fd_ = kqueue();
    return fd_ != -1;
}

Kqueue::~Kqueue()
{
    if (fd_ >= 0) {
        close(fd_);
    }
}

void Kqueue::registerFd(int fd, POLLER_EVENT event, void *udata)
{
    
}

void Kqueue::unRegisterFd(int fd, POLLER_EVENT event, void *udata)
{
    
}



#elif __linux__


#endif