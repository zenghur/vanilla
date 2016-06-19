//
//  Boss.cpp
//  Vanilla
//
//  Created by ZengHongru on 16/6/19.
//
//

#include "Boss.h"

using namespace vanilla;

Boss::Boss() : processing_(false)
{
    
}


void *Boss::loop(void *para)
{
    Boss *boss = reinterpret_cast<Boss*>(para);
    if (!boss) {
        return nullptr;
    }
    
    while (boss->isProcessing()) {
        Message item;
        if (boss->pop_front(item) == -1) {
            boss->sleep(20);
            continue;
        }
        
        
    }
    
    return boss;
}

void Boss::start()
{
    thread_.start(Boss::loop, this);
}

bool Boss::isProcessing()
{
    return processing_;
}

void Boss::setProcessing(bool flag)
{
    processing_ = flag;
}

int Boss::pop_front(Message &item)
{
    return requestMessageQueue_.pop_front(item);
}

bool Boss::push_back(Message &item)
{
    return requestMessageQueue_.push_back(item);
}

void Boss::sleep(int ms)
{
    thread_.sleep(ms);
}
