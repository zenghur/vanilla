// Copyright (c) 2016 zenghur

#ifndef UTILS_THREADATTRIBUTE_H_
#define UTILS_THREADATTRIBUTE_H_

#include <pthread.h>

namespace vanilla {
class ThreadAttribute {
 public:
   ThreadAttribute();
   ~ThreadAttribute();
  
 public:
   // inherit scheduling
   int getInheritSched(int *inheritsched);
   int setInheritSched(int inheritsched);
   // scheduling parameter
   int getSchedParam(struct sched_param *param);
   int setSchedParam(struct sched_param *param);
   // scheduling policy
   int getSchedPolicy(int *policy);
   int setSchedPolicy(int policy);
   // contention scope
   int getScope(int *contentionscope);
   int setScope(int contentionscope);
   // static size
   int getStackSize(size_t *stacksize);
   int setStackSize(size_t stacksize);
   // stack address
   int getStack(void **stackaddr, size_t *stacksize);
   int setStack(void *stackaddr, size_t stacksize);
   // detach state
   int getDetachState(int *detachstate);
   int setDetachState(int detachstate);
  
 private:
   ThreadAttribute(const ThreadAttribute &) = delete;
   ThreadAttribute &operator = (const ThreadAttribute &) = delete;
   ThreadAttribute(ThreadAttribute &&) = delete;
   ThreadAttribute &operator =(ThreadAttribute &&) = delete;
  
 private:
   pthread_attr_t attr_;
  
};
}  // namespace vanilla

#endif  // UTILS_THREADATTRIBUTE_H_

