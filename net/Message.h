// Copyright (c) 2016 zenghur

#ifndef Message_h
#define Message_h

#include <memory>

#include "SessionIDDispatcher.h"

namespace vanilla {

    
class Message {
public:
    Message();
    Message(const Message &other) = default;
    Message &operator=(const Message &other) = default;
    int type_;
    SessionIDDispatcher::SessionType sessionID_;
    std::shared_ptr<char> data_;
    int size_;
};
    
    
    
    
    
    
    
    
    
    
    
}



#endif /* Message_h */
