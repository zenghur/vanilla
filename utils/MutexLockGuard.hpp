//
//  MutexLockGuard.hpp
//  Vanilla
//
//  Created by ZengHongru on 16/4/7.
//
//

#ifndef MutexLockGuard_hpp
#define MutexLockGuard_hpp

#include "Noncopyable.h"
#include "Mutex.hpp"

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
