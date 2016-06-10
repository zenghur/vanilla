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
                                         currentConnectionIdx(0),
                                         currentConnectionsCount(0)
{
    
}

int Channel::getListenerFd()
{
    return listener_->getListenerFd();
}

TcpConnection *getConnection(int sessionID)
{
    TcpConnection *connection = NULL;
    
    return connection;
}


void Channel::init()
{
    poller_  = Poller::createPoller();
    poller_->addFd(listener_->getListenerFd(), static_cast<int8_t>(PollerEvent::POLLER_IN), listener_.get());
    
    for (auto i = 0; i < MAX_CONNECTIONS; ++i) {
        std::shared_ptr<TcpConnection> connection = std::make_shared<TcpConnection>(poller_.get());
        connections.push_back(connection);
    }
}
