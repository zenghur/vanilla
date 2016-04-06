//
//  Mutex.hpp
//  Vanilla
//
//  Created by ZengHongru on 16/4/7.
//
//

#ifndef Mutex_hpp
#define Mutex_hpp

#include "Noncopyable.cpp"

#include <pthread.h>
#include <unistd.h>

// 思路 RAII
// mutex is a resource
// pthread_mutex_init & pthread_mutex_destroy

namespace vanilla {
    
class Mutex : private vanilla::Noncopyable {
public:
    Mutex();
    ~Mutex();
    void lock();
    void unLock();
private:
    pthread_mutex_t mutex_;
};
    
}



#endif /* Mutex_hpp */
