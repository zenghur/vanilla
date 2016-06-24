// Copyright (c) 2016 zenghur

#ifndef NET_EPOLL_H_
#define NET_EPOLL_H_

#include "Poller.h"

#include <vector>

#ifdef __linux__
#include <sys/epoll.h>

class Epoll : public vanilla::Poller {
 public:
  Epoll();
  virtual ~Epoll();
  
 public:
   virtual void init();
   virtual void addFd(int fd, PollerEventType mask, void *udata);
   virtual void deleteFd(int fd, PollerEventType mask);
   virtual void modFd(int fd, PollerEventType mask, void *udata);
   virtual void poll();
  
 private:
   int epollfd_;
   static const int timeout = 10;  // milliseconds
   std::vector<struct epoll_event> events_;
   static const int MAX_EVENTS = 30;
};
#endif


#endif  // NET_EPOLL_H_