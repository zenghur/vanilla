//
//  Channel.hpp
//  Vanilla
//
//  Created by ZengHongru on 16/6/10.
//
//

#ifndef Channel_h
#define Channel_h

#include "Poller.h"
#include "MessageReactor.h"
#include "Thread.h"
#include "ConcurrentQueue.h"
#include "Message.h"
#include "PassiveMessageReactor.h"
#include "IOEvent.h"


#include <vector>

namespace vanilla {
    
class TcpListener;
class TcpConnection;
    
class Channel : public IOEvent {
public:
    typedef uint64_t SessionType;
    explicit Channel(TcpListener *listener = nullptr);
    void init();
    int getListenerFd();
    int getChannelID();
    void setChannelID(int channelID);
    void start();
    static void *loop(void *para);
    TcpConnection *getConnection(int sessionID);
public:
    virtual void canRead(); // 接受连接请求
    SessionType generateSessionID();
    
    void sleep(int ms);
    bool isProcessing();
public:
    int pop(Message &item);
    bool push(Message &item);
public:
    void onMessage(Message &message);
private:
    Channel(const Channel&) = delete;
    Channel &operator=(const Channel&) = delete;
    
private:
    bool processing_;
    std::unique_ptr<Poller> poller_;
    std::unique_ptr<MessageReactor> reactor_;
    TcpListener *listener_;
    std::vector<std::shared_ptr<TcpConnection> > connections;
private:
    ConcurrentQueue<Message> responseMessageQueue_;
private:
    int channelID_;
    int currentConnectionIdx_;
    int currentConnectionsCount_;
    const static int MAX_CONNECTIONS = 10000;
    Thread thread_;
};
    
    
}

#endif /* Channel_h */
