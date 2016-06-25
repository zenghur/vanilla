// Copyright (c) 2016 zenghur

#ifndef NET_IOEVENT_H_
#define NET_IOEVENT_H_

#include "SessionIDDispatcher.h"

namespace vanilla {
class Message;    
class IOEvent {
 public:
   virtual void canRead() = 0;
   virtual void canWrite() = 0;
   virtual void receiveMsg(Message &item) = 0;
   virtual void close(int fd) = 0;
};
}  // namespace vanilla

#endif  // NET_IOEVENT_H_
