// Copyright (c) 2016 zenghur

#include "Mutex.h"

#include <iostream>

using vanilla::Mutex;

Mutex::Mutex() {
  pthread_mutex_init(&mutex_, NULL);
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