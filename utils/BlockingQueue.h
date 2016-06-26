// Copyright (c) 2016 zenghur

#ifndef UTILS_BLOCKINGQUEUE_H_
#define UTILS_BLOCKINGQUEUE_H_

#include <list>

#include "Mutex.h"
#include "ConditionVariable.h"
#include "MutexLockGuard.h"

namespace vanilla {

template <typename T>
class BlockingQueue {
 public:
   BlockingQueue();
  
   bool push_back(T &item);
   bool push_back(T &&item);
   T pop_front();
   std::size_t size();
  
 private:
   BlockingQueue(const BlockingQueue &) = delete;
   BlockingQueue &operator = (const BlockingQueue &) = delete;
   BlockingQueue(BlockingQueue &&) = delete;
   BlockingQueue && operator = (BlockingQueue &&) = delete;
  
 private:
   std::list<T> queue_;
   Mutex mutex_;
   ConditionVariable cond_;
  
};
  
template <typename T>
BlockingQueue<T>::BlockingQueue() : cond_(mutex_) {
}
  
template <typename T>
bool BlockingQueue<T>::push_back(T &item) {
  MutexLockGuard guard(mutex_);
  try {
    queue_.push_back(item);
    cond_.signal();
  } catch (...) {
    return false;
  }
  return true;
}
  
template <typename T>
bool BlockingQueue<T>::push_back(T &&item) {
  MutexLockGuard guard(mutex_);
  try {
    queue_.push_back(std::move(item));
    cond_.signal();
  } catch (...) {
    return false;
  }
  return true;
}
  
template <typename T>
T BlockingQueue<T>::pop_front() {
  MutexLockGuard guard(mutex_);
  while (queue_.empty()) {
    cond_.wait();
  }
  
  assert(!queue_.empty());
  
  T item(queue_.front());
  queue_.pop_front();
  return item;
}

template <typename T>
std::size_t BlockingQueue<T>::size() {
  MutexLockGuard guard(mutex_);
  return queue_.size();
}
  
}  // namespace vanilla


#endif  // UTILS_BLOCKINGQUEUE_H_
