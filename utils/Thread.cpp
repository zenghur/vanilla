//
//  Thread.cpp
//  Vanilla
//
//  Created by ZengHongru on 16/4/11.
//
//

#include "Thread.hpp"

using namespace vanilla;

Thread::Thread(): joinable_(true),
                  detached_(true),
                  id_(0)
{
    
}

void Thread::start(ThreadStartFun fun, void *para)
{
    pthread_create(&id_, NULL, fun, para);
}

void Thread::join()
{
    pthread_join(id_, NULL);
}


void Thread::detach()
{
    pthread_detach(id_);
}

void Thread::exit()
{
    pthread_exit(NULL);
}

pthread_t Thread::getId()
{
    return pthread_self();
}

Thread::~Thread()
{

}



