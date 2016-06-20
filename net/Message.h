// Copyright (c) 2016 zenghur

#ifndef Message_h
#define Message_h

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
    
    
    
    
    
    
    
    
    
    
    
}



#endif /* Message_h */
