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

#include "Noncopyable.h"


#include <vector>

namespace vanilla {
    
class TcpListener;
class TcpConnection;
    
class Channel : private vanilla::Noncopyable {
public:
    explicit Channel(TcpListener *listener = nullptr);
    void init();
    int getListenerFd();
    TcpConnection *getConnection(int sessionID);
private:
    std::unique_ptr<Poller> poller_;
    std::shared_ptr<TcpListener> listener_;
    std::vector<std::shared_ptr<TcpConnection> > connections;
private:
    int currentConnectionIdx;
    int currentConnectionsCount;
    const static int MAX_CONNECTIONS = 10000;
};
    
    
}

#endif /* Channel_h */
