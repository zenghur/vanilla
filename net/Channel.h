// Copyright (c) 2016 zenghur

#ifndef Channel_h
#define Channel_h

#include "Poller.h"
#include "Thread.h"
#include "ConcurrentQueue.h"
#include "Message.h"
#include "IOEvent.h"


#include <vector>

namespace vanilla {
    
class TcpListener;
class TcpConnection;
    
class Channel : public IOEvent {
public:
    typedef uint64_t SessionType;
    explicit Channel(TcpListener *listener = nullptr);
    void init(int channelID);
    int getListenerFd();
    int getChannelID();
    void setChannelID(int channelID);
    void start();
    void join();
    static void *loop(void *para);
    TcpConnection *getConnection(SessionType sessionID);
public:
    virtual void canRead(); // 接受连接请求
    virtual void canWrite();
    SessionType generateSessionID();
    
    void sleep(int ms);
    bool isProcessing();
    void setProcessing(bool flag);
public:
    int pop_front(Message &item);
    bool push_back(Message &item);
public:
    void onMessage(Message &message);    
private:
    bool processing_;
    std::unique_ptr<Poller> poller_;
    TcpListener *listener_;
    std::vector<std::shared_ptr<TcpConnection> > connections_;
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
