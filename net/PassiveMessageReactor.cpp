//
//  PassiveMessageReactor.cpp
//  Vanilla
//
//  Created by ZengHongru on 16/6/17.
//
//

#include "PassiveMessageReactor.h"
#include "MessageType.h"


using namespace vanilla;

PassiveMessageReactor::PassiveMessageReactor()
{
    
}

PassiveMessageReactor::~PassiveMessageReactor()
{
    
}

void PassiveMessageReactor::setPoller(Poller *poller)
{
    poller_ = poller;
}

void PassiveMessageReactor::onMessage(Message &message)
{
    switch (message.type_) {
        case Vanilla::MessageType::NET_MSG: {
            
            break;
        }
        case Vanilla::MessageType::TIMER_MSG: {
            poller_->poll();
            break;
        }
        default: {
            break;
        }
    }
}


