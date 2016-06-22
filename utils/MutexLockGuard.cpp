// Copyright (c) 2016 zenghur

#include "MutexLockGuard.h"

using vanilla::MutexLockGuard;

MutexLockGuard::MutexLockGuard(Mutex &m): mutex_(m) {
  mutex_.lock();
}

MutexLockGuard::~MutexLockGuard() {
  mutex_.unLock();
}