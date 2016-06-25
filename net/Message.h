// Copyright (c) 2016 zenghur

#ifndef NET_MESSAGE_H_
#define NET_MESSAGE_H_

#include <memory>
#include <vector>

#include "SessionIDDispatcher.h"

// rule of zero

namespace vanilla {
struct Message {
  Message() = default;
  Message(const Message &item) = default;
  Message& operator = (const Message &item) = default;
  Message(Message &&item) = default;
  Message& operator = (Message &&item) = default;
  ~Message() = default;
  
  int type_;
  SessionIDDispatcher::SessionType sessionID_;
  std::vector<char> data_;
  int size_;
};
}  // namespace vanilla

#endif  // NET_MESSAGE_H_ 
