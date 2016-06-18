//
//  Message.cpp
//  Vanilla
//
//  Created by ZengHongru on 16/6/18.
//
//

#include "Message.h"

#include <utility>

using namespace vanilla;


Message::Message(): type_(0),
                    sessionID_(0),
                    data_(nullptr),
                    size_(0)
{
    
}

