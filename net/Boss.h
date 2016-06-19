//
//  Boss.hpp
//  Vanilla
//
//  Created by ZengHongru on 16/6/19.
//
//

#ifndef Boss_h
#define Boss_h

#include "ConcurrentQueue.h"
#include "Message.h"
#include "Thread.h"

namespace vanilla {

class Boss {
public:
    Boss();
    static void *loop(void *para);
    void start();
    
    bool isProcessing();
    void setProcessing(bool flag);
    
    int pop_front(Message &item);
    bool push_back(Message &item);
    
    void sleep(int ms);
    
private:
    Boss(const Boss &) = delete;
    Boss &operator = (const Boss &) = delete;
    
private:
    bool processing_;
    ConcurrentQueue<Message> requestMessageQueue_;
    Thread thread_;
};
    
    
    
}



#endif /* Boss_h */
