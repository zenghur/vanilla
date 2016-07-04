// Copyright (c) 2016 zenghur

#include "Thread.h"

#include <iostream>
#include <cassert>

#include "DateTime.h"
#include "Error.h"

using vanilla::Thread;

Thread::Thread(): joinable_(true),
                  detached_(true),
                  handle_(0) {
}

void Thread::start(ThreadStartFun fun, void *para) {
  pthread_create(&handle_, nullptr, fun, para);
}

void Thread::sleep(int ms) {
  struct timeval val = DateTime::msToTimeval(ms);
  select(0, nullptr, nullptr, nullptr, &val);
}

void Thread::join() {
  assert(joinable_);
  int status = pthread_join(handle_, nullptr);
  if (status != 0) {
    threadError(status);
  }
  joinable_ = false;
  detached_ = false;
}

void Thread::detach() {
  assert(detached_);
  int status = pthread_detach(handle_);
  if (status != 0) {
    threadError(status);
  }
  joinable_ = false;
  detached_ = false;
}

void Thread::exit() {
  pthread_exit(nullptr);
}

pthread_t Thread::getId() {
  return pthread_self();
}

void Thread::cancel() {
  int status  = pthread_cancel(handle_);
  if (status != 0) {
    threadError(status);
  }
}




