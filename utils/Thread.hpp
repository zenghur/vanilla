//
//  Thread.hpp
//  Vanilla
//
//  Created by ZengHongru on 16/4/11.
//
//

#ifndef Thread_hpp
#define Thread_hpp

#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>

#include "Noncopyable.h"

namespace vanilla {
    
    
class Thread : private vanilla::Noncopyable {
public:
    typedef void *(*ThreadStartFun)(void *);
    Thread();
    void start(ThreadStartFun fun, void *para);
    void join();
    void detach();
    void exit();
    pthread_t getId();
    ~Thread();
private:
    bool joinable_;
    bool detached_;
    pthread_t id_;
    
};
    
}




#endif /* Thread_hpp */
