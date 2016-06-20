// Copyright (c) 2016 zenghur

#ifndef IOModule_h
#define IOModule_h

#include <vector>

#include "Channel.h"
#include "Boss.h"

namespace vanilla {
class IOModule {
public:
    void init(std::string ip, uint16_t port);
    void start();
private:
    std::shared_ptr<TcpListener> listener_;
    std::vector<std::shared_ptr<Channel> > channels_;
    std::shared_ptr<Boss> boss_;
private:
    static const int NUM_OF_POLLERS = 2;
};
    
    
}






#endif /* IOModule_h */
