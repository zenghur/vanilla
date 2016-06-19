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
#include "Endian.h"
#include "SessionIDDispatcher.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <arpa/inet.h>

#include <string>
#include <iostream>

using namespace vanilla;

Channel::Channel(TcpListener *listener): poller_(nullptr),
                                         listener_(listener),
                                         processing_(false),
                                         currentConnectionIdx_(0),
                                         currentConnectionsCount_(0)
{
    
}

int Channel::getListenerFd()
{
    return listener_->getListenerFd();
}

int Channel::getChannelID()
{
    return channelID_;
}

void Channel::setChannelID(int channelID)
{
    channelID_ = channelID;
}

vanilla::Channel::SessionType Channel::generateSessionID()
{
    if (currentConnectionsCount_ >= MAX_CONNECTIONS) {
        return 0;
    }
    
    int hole = 0;
    for (int i = 0; i < MAX_CONNECTIONS; ++i) {
        hole = (currentConnectionIdx_ + i) % MAX_CONNECTIONS;
        if (connections_[hole]->getConnectionFd() == -1) {
            currentConnectionIdx_  =  hole;
            ++currentConnectionsCount_;
            SessionType sessionID = SessionIDDispatcher::getSessionId(1, getChannelID(), hole);
            return sessionID;
        }
    }
    
    return 0;
}

bool Channel::isProcessing()
{
    return processing_ == true;
}

void Channel::sleep(int ms)
{
    thread_.sleep(ms);
}

int Channel::pop_front(Message &item)
{
   return responseMessageQueue_.pop_front(item);
}

bool Channel::push_back(Message &item)
{
    return responseMessageQueue_.push_back(item);
}

void Channel::onMessage(Message &message)
{
    reactor_->onMessage(message);
}

void Channel::start()
{
    thread_.start(loop, this);
}

void Channel::join()
{
    thread_.join();
}

void Channel::canRead()
{
    do {
        
        struct sockaddr_in clientAddr;
        socklen_t len = sizeof(socklen_t);
        
        // non-blocking accept;
        int clientFd = ::accept(listener_->getListenerFd(), reinterpret_cast<struct sockaddr *>(&clientAddr), &len);
        
        if (clientFd < 0) {
            
            if (errno == EAGAIN || errno == EWOULDBLOCK)
                break;
            
            if (errno == EINTR) {
                continue;
            }
        }
        
        SessionType sessionID = generateSessionID();
        
        if (sessionID == 0) {
            ::close(clientFd);
            continue;
        }
        std::shared_ptr<TcpConnection> connection = std::make_shared<TcpConnection>(poller_.get());
        connection->init(clientFd, sessionID);
        connections_[currentConnectionIdx_] = connection;
        
        int port = be16toh(clientAddr.sin_port);
        std::string ip(inet_ntoa(clientAddr.sin_addr));
        
        std::cout << ip << ":" << port << std::endl;
        
        
        
    } while (true);
}

void Channel::canWrite()
{
    
}

void *Channel::loop(void *para)
{
    Channel *channel = reinterpret_cast<Channel *>(para);
    
    if (!channel) {
        return channel;
    }
    
    while (channel->isProcessing()) {
        Message item;
        if (channel->pop_front(item) == -1) {
            channel->sleep(20);
            continue;
        }
        channel->onMessage(item);
    }
    
    return channel;
}

TcpConnection *Channel::getConnection(SessionType sessionID)
{
    TcpConnection *connection = nullptr;
    int hole = SessionIDDispatcher::getAutoIncrementID(sessionID);
    if (hole >= 0 || hole < MAX_CONNECTIONS) {
        connection = connections_[hole].get();
    }
    return connection;
}


void Channel::init(int channelID)
{
    poller_  = Poller::createPoller();
    poller_->addFd(listener_->getListenerFd(), static_cast<Poller::PollerEventType>(PollerEvent::POLLER_IN), listener_);
    processing_ = true;
    
    for (auto i = 0; i < MAX_CONNECTIONS; ++i) {
        std::shared_ptr<TcpConnection> connection = std::make_shared<TcpConnection>(poller_.get());
        connections_.push_back(connection);
    }
    
    setChannelID(channelID);
}
