// Copyright (c) 2016 zenghur

#ifndef  UTILS_CONCURRENTQUEUE_H_
#define  UTILS_CONCURRENTQUEUE_H_

#include <deque>

#include "Mutex.h"
#include "MutexLockGuard.h"

namespace vanilla {
template<typename T>
class ConcurrentQueue {
 public:
   bool  push_back(T &item);
   int pop_front(T &item);
   int size();
  
 private:
   std::deque<T> queue_;
   mutable Mutex mutex_;
};
    
template<typename T>
bool ConcurrentQueue<T>::push_back(T &item) {
  MutexLockGuard guard(mutex_);
  try {
    queue_.push_back(std::move(item));
  } catch(...) {
    return false;
  }
  return true;
}
    
template<typename T>
int ConcurrentQueue<T>::pop_front(T &item) {
  MutexLockGuard guard(mutex_);
  if (!queue_.empty()) {
    item = std::move(queue_.front());
    queue_.pop_front();
    return 0;
  }
  return -1;
}

template<typename T>
int vanilla::ConcurrentQueue<T>::size() {
  MutexLockGuard guard(mutex_);
  return queue_.size();
}
    
}  // namespace vanilla

#endif  //  UTILS_CONCURRENTQUEUE_H_
