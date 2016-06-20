// Copyright (c) 2016 zenghur

#include "Message.h"

#include <utility>

using namespace vanilla;


Message::Message(): type_(0),
                    sessionID_(0),
                    data_(nullptr),
                    size_(0)
{
    
}

