// Copyright (c) 2016 zenghur

#include "Kqueue.h"

#include "Error.h"
#include "DateTime.h"
#include "IOEvent.h"

using vanilla::printError;
using vanilla::PollerEvent;
using vanilla::IOEvent;
using vanilla::DateTime;

#ifdef __APPLE__

Kqueue::Kqueue(): kqfd_(-1), events_(MAX_EVENTS) {
}

Kqueue::~Kqueue() {
  if (kqfd_ >= 0) {
    close(kqfd_);
  }
}

void Kqueue::init() {
  if ((kqfd_ = kqueue()) == -1) {
    printError();
  }
}

void Kqueue::addFd(int fd, PollerEventType mask, void *udata) {
  struct kevent event;
  if (mask & static_cast<PollerEventType>(PollerEvent::POLLER_IN)) {
    EV_SET(&event, fd, EVFILT_READ, EV_ADD, 0, 0, udata);
    if (kevent(kqfd_, &event, 1, nullptr, 0, nullptr) == -1) {
      printError();
    }
  }
  if (mask & static_cast<PollerEventType>(PollerEvent::POLLER_OUT)) {
    EV_SET(&event, fd, EVFILT_WRITE, EV_ADD, 0, 0, udata);
    if (kevent(kqfd_, &event, 1, nullptr, 0, nullptr) == -1) {
      printError();
    }
  }
}

void Kqueue::deleteFd(int fd, PollerEventType mask) {
  struct kevent event;
  if (static_cast<PollerEventType>(mask) & static_cast<PollerEventType>(PollerEvent::POLLER_IN)) {
    EV_SET(&event, fd, EVFILT_READ, EV_DELETE, 0, 0, nullptr);
    if (kevent(kqfd_, &event, 1, nullptr, 0, nullptr) == -1) {
      printError();
    }
  }
  if (static_cast<PollerEventType>(mask) & static_cast<PollerEventType>(PollerEvent::POLLER_OUT)) {
    EV_SET(&event, fd, EVFILT_WRITE, EV_DELETE, 0, 0, nullptr);
    if (kevent(kqfd_, &event, 1, nullptr, 0, nullptr) == -1) {
      printError();
    }
  }
}

//  kevent不用判断返回值
void Kqueue::modFd(int fd, PollerEventType mask, void *udata) {
  struct kevent event;
  if (static_cast<PollerEventType>(mask) & static_cast<PollerEventType>(PollerEvent::POLLER_IN)) {
    EV_SET(&event, fd, EVFILT_READ, EV_ADD, 0, 0, udata);
  } else {
    EV_SET(&event, fd, EVFILT_READ, EV_DELETE, 0, 0, udata);
  }
  kevent(kqfd_, &event, 1, nullptr, 0, nullptr);
  
  if (static_cast<PollerEventType>(mask) & static_cast<PollerEventType>(PollerEvent::POLLER_OUT)) {
    EV_SET(&event, fd, EVFILT_WRITE, EV_ADD, 0, 0, udata);
  } else {
    EV_SET(&event, fd, EVFILT_WRITE, EV_DELETE, 0, 0, udata);
  }
  kevent(kqfd_, &event, 1, nullptr, 0, nullptr);
}

void Kqueue::poll() {
  int n = 0;
  struct timespec spec = DateTime::msToTimespec(timeout);
  if ((n = kevent(kqfd_, nullptr, 0, &*events_.begin(), events_.size(), &spec)) == -1) {
    printError();
  }
  for (size_t index = 0; index < n; ++index) {
    IOEvent *io = reinterpret_cast<IOEvent*>(events_[index].udata);
    if (!io) {
      continue;
    }
    if ((events_[index].flags & EV_ERROR) || (events_[index].flags & EV_EOF)) {
      io->close(events_[index].ident);
    } else if (events_[index].filter == EVFILT_READ) {
      io->canRead();
    } else if (events_[index].filter == EVFILT_WRITE) {
      io->canWrite();
    }
  }
}

#endif

