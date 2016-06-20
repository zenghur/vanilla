// Copyright (c) 2016 zenghur

#ifndef THREAD_H
#define THREAD_H

#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>



#include "Noncopyable.h"

namespace vanilla {
    
    
class Thread : private vanilla::Noncopyable {
public:
    typedef void *(*ThreadStartFun)(void *);
    Thread();
    void sleep(int ms);
    void start(ThreadStartFun fun, void *para);
    void join();
    void detach();
    void exit();
    pthread_t getId();
    void cancel();
    ~Thread();
private:
    bool joinable_;
    bool detached_;
    pthread_t handle_;
    
};
    
}


#endif
