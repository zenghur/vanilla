// Copyright (c) 2016 zenghur

#ifndef UTILS_MUTEXLOCKGUARD_H_
#define UTILS_MUTEXLOCKGUARD_H_

#include "Mutex.h"

namespace vanilla {
class MutexLockGuard {
 public:
   explicit MutexLockGuard(Mutex &m);
   ~MutexLockGuard();
  
 private:
   MutexLockGuard(const MutexLockGuard &) = delete;
   MutexLockGuard& operator = (const MutexLockGuard &) = delete;
   Mutex &mutex_;
};
}  // namespace vanilla

#endif  // UTILS_MUTEXLOCKGUARD_H_
