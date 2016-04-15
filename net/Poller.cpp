//
//  Poller.cpp
//  Vanilla
//
//  Created by ZengHongru on 16/4/15.
//
//

#include "Poller.h"

using namespace vanilla;

#ifdef __APPLE__
#include "Kqueue.h"

std::unique_ptr<Poller> Poller::createPoller()
{
    std::unique_ptr<Poller> p(new Kqueue());
    p->init();
    return std::move(p);
}

#elif __linux__

std::unique_ptr<Poller> Poller::createPoller()
{
    std::unique_ptr<Poller> p(new Epoll());
    p->init();
    return std::move(p);
}


#endif