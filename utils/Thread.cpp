// @author: zenghongru@gmail.com

#include "Thread.h"

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



