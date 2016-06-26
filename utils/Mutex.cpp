// Copyright (c) 2016 zenghur

#include "Mutex.h"

#include "MutexLockGuard.h"

using vanilla::Mutex;

Mutex::Mutex() {
  pthread_mutex_init(&mutex_, nullptr);
}

Mutex::~Mutex() {
  pthread_mutex_destroy(&mutex_);
}

void Mutex::lock() {
  pthread_mutex_lock(&mutex_);
}

void Mutex::unLock() {
  pthread_mutex_unlock(&mutex_);
}

pthread_mutex_t &Mutex::getPthreadMutex() {
  return mutex_;
}