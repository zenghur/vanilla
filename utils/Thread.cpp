// @author: zenghongru@gmail.com

#include "Thread.h"

using namespace vanilla;

Thread::Thread(): joinable_(true),
                  detached_(true),
                  handle_(0)
{
    
}

void Thread::start(ThreadStartFun fun, void *para)
{
    pthread_create(&handle_, NULL, fun, para);
}

void Thread::join()
{
    pthread_join(handle_, NULL);
}


void Thread::detach()
{
    pthread_detach(handle_);
}

void Thread::exit()
{
    pthread_exit(NULL);
}

pthread_t Thread::getId()
{
    return pthread_self();
}

void Thread::cancel()
{
    pthread_cancel(handle_);
}

Thread::~Thread()
{

}



