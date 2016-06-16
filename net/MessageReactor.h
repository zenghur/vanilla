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

namespace vanilla {

enum class MessageReactorType : int {
    ACCEPT = 0,
    READ = 1,
    DISCONNECT = 2,
    CONNECT = 3
};
    
class MessageReactor {
public:
    virtual void onMessage(int sessionID, MessageReactorType type, char *data, int len) = 0;
    virtual ~MessageReactor() {}
};
    
    
    
    
}

#endif /* MessageReactor_h */
