// Copyright (c) 2016 zenghur

#include "Epoll.h"

#include <string.h>

#include "Error.h"
#include "DateTime.h"
#include "IOEvent.h"

using vanilla::printError;
using vanilla::PollerEvent;
using vanilla::IOEvent;
using vanilla::DateTime;

#ifdef __linux__
#include <sys/epoll.h>

Epoll::Epoll(): epollfd_(-1), events_(MAX_EVENTS) {
}

Epoll::~Epoll() {
  if (epollfd_ >= 0) {
    close(epollfd_);
  }
}

void Epoll::init() {
  if ((epollfd_ = epoll_create(1)) == -1) {
    printError();
  }
}

void Epoll::addFd(int fd, PollerEventType mask, void *udata) {
  struct epoll_event event;
  memset(&event, 0, sizeof(event);
  if (mask & static_cast<PollerEventType>(PollerEvent::POLLER_IN)) {
    event.events |= EPOLLIN;
  }
  if (mask & static_cast<PollerEventType>(PollerEvent::POLLER_OUT)) {
    event.events |= EPOLLOUT;
  }
  event.data.ptr = udata;
  if (epoll_ctl(epollfd_, EPOLL_CTL_ADD, fd, &events) == -1) {
    printError();
  }
}

void Epoll::deleteFd(int fd, PollerEventType mask) {
  epoll_ctl(epollfd_, EPOLL_CTL_DEL, fd, NULL);
}
         
void Epoll::modFd(int fd, PollerEventType mask, void *udata) {
  struct epoll_event event;
  memset(&event, 0, sizeof(event);
  if (mask & static_cast<PollerEventType>(PollerEvent::POLLER_IN)) {
   event.events |= EPOLLIN;
  }
  if (mask & static_cast<PollerEventType>(PollerEvent::POLLER_OUT)) {
   event.events |= EPOLLOUT;
  }
  event.data.ptr = udata;
  epoll_ctl(epollfd_, EPOLL_CTL_MOD, fd, &events);
}

void Epoll::poll() {
  int n = 0;
  if ((n = epoll_wait(epollfd_, &*events_.begin(), MAX_EVENTS, timeout)) == -1) {
    printError();
  }
  for (auto i = 0; i < n; ++i) {
    IOEvent *io = events_[i].data.ptr;
    if (!io) {
      continue;
    }
    if (events[i].events & EPOLLIN) {
      io->canRead();
    }
    if (events[i].events & EPOLLIN || events[i].events & EPOLLERR) {
      io->canWrite();
    }
  }
}




#endif
