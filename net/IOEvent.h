//
//  IOEvent.hpp
//  Vanilla
//
//  Created by ZengHongru on 16/6/5.
//
//

#ifndef IOEvent_h
#define IOEvent_h

#include "Noncopyable.h"

namespace vanilla {

class IOEvent : private vanilla::Noncopyable {
public:
    virtual void canRead() = 0;
    virtual void canWrite() = 0;
};


    
    
}

#endif /* IOEvent_h */
