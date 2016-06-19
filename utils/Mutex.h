//
//  Mutex.hpp
//  Vanilla
//
//  Created by ZengHongru on 16/4/7.
//
//

#ifndef Mutex_hpp
#define Mutex_hpp

#include "Noncopyable.h"

#include <pthread.h>
#include <unistd.h>

// 思路 RAII
// mutex is a resource
// pthread_mutex_init & pthread_mutex_destroy

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
    
}



#endif /* Mutex_hpp */
