// Copyright (c) 2016 zenghur

#ifndef UTILS_MUTEX_H_
#define UTILS_MUTEX_H_

#include <pthread.h>
#include <unistd.h>

// 思路 RAII
// mutex is a resource

namespace vanilla {
class Mutex {
 public:
    Mutex();
    ~Mutex();
    void lock();
    void unLock();
    
 private:
    Mutex(const Mutex &) = delete;
    Mutex & operator = (const Mutex &) = delete;
    pthread_mutex_t mutex_;
};
}  // namespace vanilla

#endif  // UTILS_MUTEX_H_
