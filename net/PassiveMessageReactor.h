//
//  PassiveMessageReactor.hpp
//  Vanilla
//
//  Created by ZengHongru on 16/6/17.
//
//

#ifndef PassiveMessageReactor_h
#define PassiveMessageReactor_h

#include "Noncopyable.h"
#include "MessageReactor.h"

namespace vanilla {
    
class PassiveMessageReactor : public MessageReactor {
public:
    PassiveMessageReactor();
    virtual void onMessage(int sessionID, MessageReactorType type, char *data, int len);
    virtual ~PassiveMessageReactor();
private:
    PassiveMessageReactor(const PassiveMessageReactor &) = delete;
    PassiveMessageReactor &operator = (const PassiveMessageReactor &) = delete;
};
    
}

#endif /* PassiveMessageReactor_h */
