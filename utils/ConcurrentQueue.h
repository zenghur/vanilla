//
//  ConcurrentQueue.hpp
//  Vanilla
//
//  Created by ZengHongru on 16/6/18.
//
//

#ifndef ConcurrentQueue_h
#define ConcurrentQueue_h

#include <list>

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
    std::list<T> queue_;
    mutable Mutex mutex_;
};
    
template<typename T>
bool ConcurrentQueue<T>::push_back(T &item)
{
    MutexLockGuard guard(mutex_);
    try {
        queue_.push_back(item);
    }
    catch(...) {
        return false;
    }
    return true;
}
    
template<typename T>
int ConcurrentQueue<T>::pop_front(T &item)
{
    MutexLockGuard guard(mutex_);
    if (!queue_.empty()) {
        item = queue_.front();
        queue_.pop_front();
        return 0;
    }
    return -1;
}

template<typename T>
int vanilla::ConcurrentQueue<T>::size()
{
    MutexLockGuard guard(mutex_);
    return queue_.size();
}
    
}



#endif /* ConcurrentQueue_h */
