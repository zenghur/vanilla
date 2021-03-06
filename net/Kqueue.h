// Copyright (c) 2016 zenghur

#ifndef NET_KQUEUE_H_
#define NET_KQUEUE_H_

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
   virtual void addFd(int fd, PollerEventType mask, void *udata);
   virtual void deleteFd(int fd, PollerEventType mask);
   virtual void modFd(int fd, PollerEventType mask, void *udata);
   virtual void poll();
  
 private:
   static const int timeout = 10;  // milliseconds
   static const int MAX_EVENTS = 30;
   std::vector<struct kevent> events_;
   int kqfd_;
};

#endif

#endif  // NET_KQUEUE_H_