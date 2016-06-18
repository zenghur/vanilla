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
#include "Poller.h"

namespace vanilla {
    
class PassiveMessageReactor : public MessageReactor {
public:
    PassiveMessageReactor();
    void setPoller(Poller *poller);
    virtual void onMessage(Message &message);
    virtual ~PassiveMessageReactor();
private:
    PassiveMessageReactor(const PassiveMessageReactor &) = delete;
    PassiveMessageReactor &operator = (const PassiveMessageReactor &) = delete;
private:
    Poller *poller_;
};
    
}

#endif /* PassiveMessageReactor_h */
