// Copyright (c) 2016 zenghur

#ifndef UTILS_THREAD_H_
#define UTILS_THREAD_H_

#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>

namespace vanilla {
class Thread {
 public:
   typedef void *(*ThreadStartFun)(void *);
   Thread();
   void sleep(int ms);
   void start(ThreadStartFun fun, void *para);
   void join();
   void detach();
   void exit();
   pthread_t getId();
   void cancel();
  
 private:
   Thread(const Thread &) = delete;
   Thread& operator = (const Thread &) = delete;
   bool joinable_;
   bool detached_;
   pthread_t handle_;
};
}  // namespace vanilla


#endif  // UTILS_THREAD_H_
