//
//  Channel.cpp
//  Vanilla
//
//  Created by ZengHongru on 16/6/10.
//
//

#include "Channel.h"
#include "TcpListener.h"
#include "TcpConnection.h"

using namespace vanilla;

Channel::Channel(TcpListener *listener): poller_(nullptr),
                                         listener_(listener),
                                         processing_(false),
                                         currentConnectionIdx(0),
                                         currentConnectionsCount(0)
{
    
}

int Channel::getListenerFd()
{
    return listener_->getListenerFd();
}

bool Channel::isProcessing()
{
    return processing_ == true;
}

void Channel::sleep(int ms)
{
    thread_.sleep(ms);
}

void Channel::start()
{
    thread_.start(loop, this);
}

void *Channel::loop(void *para)
{
    Channel *channel = reinterpret_cast<Channel *>(para);
    
    if (!channel) {
        return channel;
    }
    
    while (channel->isProcessing()) {
        
    }
    
    return channel;
}

TcpConnection *getConnection(int sessionID)
{
    TcpConnection *connection = NULL;
    
    return connection;
}


void Channel::init()
{
    poller_  = Poller::createPoller();
    poller_->addFd(listener_->getListenerFd(), static_cast<int8_t>(PollerEvent::POLLER_IN), listener_);
    processing_ = true;
    
    for (auto i = 0; i < MAX_CONNECTIONS; ++i) {
        std::shared_ptr<TcpConnection> connection = std::make_shared<TcpConnection>(poller_.get());
        connections.push_back(connection);
    }
}
