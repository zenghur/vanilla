// Copyright (c) 2016 zenghur

#ifndef NET_POLLER_H_
#define NET_POLLER_H_

#include "Noncopyable.h"

#include <unistd.h>
#include <sys/types.h>

#include <memory>

namespace vanilla {
class Poller {
 public:
  typedef uint32_t PollerEventType;
  static std::unique_ptr<Poller> createPoller();
  Poller() = default;
  
 public:
  virtual void poll() = 0;
  virtual void init() = 0;
  virtual void addFd(int fd, PollerEventType mask, void *udata) = 0;
  virtual void deleteFd(int fd, PollerEventType mask) = 0;
  virtual void modFd(int fd, PollerEventType mask, void *udata) = 0;
  virtual ~Poller() {};
  
 private:
  Poller(const Poller&) = delete;
  Poller& operator = (const Poller &) = delete;
};
enum class PollerEvent: Poller::PollerEventType {
    POLLER_IN = 0x00000001,  // readable
    POLLER_OUT = 0x00000010  // writable
};
}  // namespace vanilla

#endif  // NET_POLLER_H_