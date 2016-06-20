// Copyright (c) 2016 zenghur

#include "Thread.h"
#include "DateTime.h"
#include "Error.h"
#include <iostream>

#include <cassert>

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

void Thread::sleep(int ms)
{
    struct timeval val = DateTime::msToTimeval(ms);
    select(0, NULL, NULL, NULL, &val);
}

void Thread::join()
{
    assert(joinable_);
    if (!pthread_join(handle_, NULL)) {
        printError();
    }
    joinable_ = false;
    detached_ = false;
}


void Thread::detach()
{
    assert(detached_);
    pthread_detach(handle_);
    joinable_ = false;
    detached_ = false;
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



