// Copyright (c) 2016 zenghur

#ifndef UTILS_CONDITIONVARIABLE_H_
#define UTILS_CONDITIONVARIABLE_H_

#include "Mutex.h"

#include <pthread.h>
#include <sys/types.h>

namespace vanilla {
class ConditionVariable {
 public:
   explicit ConditionVariable(Mutex &mutex);
   ~ConditionVariable();
   void broadcast();
   void signal();
   void wait();
   void timewait(int ms);
  
 private:
   ConditionVariable(const ConditionVariable &) = delete;
   ConditionVariable &operator = (const ConditionVariable &) = delete;
  
 private:
   pthread_cond_t cond_;
   Mutex &mutex_;
};
}  // namespace vanilla

#endif  // UTILS_CONDITIONVARIABLE_H_