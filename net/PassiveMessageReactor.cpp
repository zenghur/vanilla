//
//  PassiveMessageReactor.cpp
//  Vanilla
//
//  Created by ZengHongru on 16/6/17.
//
//

#include "PassiveMessageReactor.h"


using namespace vanilla;

PassiveMessageReactor::PassiveMessageReactor()
{
    
}

PassiveMessageReactor::~PassiveMessageReactor()
{
    
}

void PassiveMessageReactor::onMessage(int sessionID, MessageReactorType type, char *data, int len)
{
    switch (type) {
        case MessageReactorType::ACCEPT: {
            break;
        }
        case MessageReactorType::READ: {
            break;
        }
        case MessageReactorType::DISCONNECT: {
            break;
        }
        default: {
            break;
        }
    }
}


