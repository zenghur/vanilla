// Copyright (c) 2016 zenghur

#ifndef NET_EPOLL_H_
#define NET_EPOLL_H_

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
   virtual void modFd(int fd, POLLER_EVENT event, void *udata);
   virtual void poll();
  
 private:
   int epollfd_;
   static const int timeout = 1;
   struct epoll_event events_;
   static const int MAX_EVENTS = 30;
};
#endif


#endif  // NET_EPOLL_H_