//
//  MessageReactor.hpp
//  Vanilla
//
//  Created by ZengHongru on 16/6/17.
//
//

#ifndef MessageReactor_h
#define MessageReactor_h

#include <memory>
#include "SessionIDDispatcher.h"
#include "Message.h"

namespace vanilla {
    
class MessageReactor {
public:
    virtual void onMessage(Message &message) = 0;
    virtual ~MessageReactor() {}
};
    
    
    
    
}

#endif /* MessageReactor_h */
