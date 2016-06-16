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

#include "Noncopyable.h"
#include "Thread.h"


#include <vector>

namespace vanilla {
    
class TcpListener;
class TcpConnection;
    
class Channel : private vanilla::Noncopyable {
public:
    explicit Channel(TcpListener *listener = nullptr);
    void init();
    int getListenerFd();
    void start();
    static void *loop(void *para);
    TcpConnection *getConnection(int sessionID);
    
    void sleep(int ms);
    bool isProcessing();
    
private:
    bool processing_;
    std::unique_ptr<Poller> poller_;
    std::unique_ptr<MessageReactor> reactor_;
    TcpListener *listener_;
    std::vector<std::shared_ptr<TcpConnection> > connections;
private:
    int currentConnectionIdx;
    int currentConnectionsCount;
    const static int MAX_CONNECTIONS = 10000;
    Thread thread_;
};
    
    
}

#endif /* Channel_h */
