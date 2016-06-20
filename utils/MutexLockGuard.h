// Copyright (c) 2016 zenghur

#ifndef MutexLockGuard_hpp
#define MutexLockGuard_hpp

#include "Noncopyable.h"
#include "Mutex.h"

namespace vanilla {

class MutexLockGuard : private vanilla::Noncopyable {
public:
    explicit MutexLockGuard(Mutex &m);
    ~MutexLockGuard();
private:
    Mutex &mutex_;
};
    
    
}

#endif /* MutexLockGuard_hpp */
