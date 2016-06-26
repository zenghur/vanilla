// Copyright (c) 2016 zenghur

#include "ConditionVariable.h"

#include "DateTime.h"

using vanilla::ConditionVariable;
using vanilla::DateTime;

ConditionVariable::ConditionVariable(Mutex &mutex) : mutex_(mutex) {
  pthread_cond_init(&cond_, nullptr);
}

ConditionVariable::~ConditionVariable() {
  pthread_cond_destroy(&cond_);
}

void ConditionVariable::broadcast() {
  pthread_cond_broadcast(&cond_);
}

void ConditionVariable::signal() {
  pthread_cond_signal(&cond_);
}

void ConditionVariable::wait() {
  pthread_cond_wait(&cond_, &mutex_.getPthreadMutex());
}

void ConditionVariable::timewait(int ms) {
  struct timespec spec = DateTime::msToTimespec(ms);
  pthread_cond_timedwait(&cond_, &mutex_.getPthreadMutex(), &spec);
}


