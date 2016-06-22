// Copyright (c) 2016 zenghur

#include "Poller.h"

using vanilla::Poller;

#ifdef __APPLE__
#include "Kqueue.h"

std::unique_ptr<Poller> Poller::createPoller() {
  std::unique_ptr<Poller> p(new Kqueue());
  p->init();
  return std::move(p);
}

#elif __linux__
#include "Epoll.h"

std::unique_ptr<Poller> Poller::createPoller() {
  std::unique_ptr<Poller> p(new Epoll());
  p->init();
  return std::move(p);
}

#endif