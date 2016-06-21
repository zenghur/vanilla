// Copyright (c) 2016 zenghur

#ifndef NET_MESSAGE_H_
#define NET_MESSAGE_H_

#include <memory>
#include <vector>

#include "SessionIDDispatcher.h"

namespace vanilla {
struct Message {
    Message();
    int type_;
    SessionIDDispatcher::SessionType sessionID_;
    char* data_;
    int size_;
};
}  // namespace vanilla

#endif  // NET_MESSAGE_H_ 
