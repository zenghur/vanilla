//
//  IOModule.cpp
//  Vanilla
//
//  Created by ZengHongru on 16/6/19.
//
//

#include <memory>

#include "IOModule.h"
#include "TcpListener.h"

using namespace vanilla;

void IOModule::init(std::string ip, uint16_t port)
{
    listener_ = std::make_shared<TcpListener>();
    listener_->listen(ip, port);
    
    for (auto i = 0; i < NUM_OF_POLLERS; ++i) {
        std::shared_ptr<Channel> channel = std::make_shared<Channel>(listener_.get());
        channel->init(channels_.size());
        channels_.push_back(channel);
    }
    
    boss_ = std::make_shared<Boss>();
    
    start();
    
}

void IOModule::start()
{
    for (auto i = 0; i < NUM_OF_POLLERS; ++i) {
        channels_[i]->start();
    }
    
    boss_->start();
    
    for (auto i = 0; i < NUM_OF_POLLERS; ++i) {
        channels_[i]->join();
    }
    
    boss_->join();
}

