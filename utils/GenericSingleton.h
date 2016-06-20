// Copyright (c) 2016 zenghur

// Double-checked locking pattern(DCLP)的做法有问题，stackoverflow有讨论。
// Scott Meyers and Andrei Alexandrescu对此有话要说！文章名叫C++ and the Perils of Double-Checked Locking。

#ifndef GenericSingleton_h
#define GenericSingleton_h

#include "Noncopyable.h"

#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>

#include <cstdlib>

namespace vanilla {
    
template <typename T>
class GenericSingleton : private vanilla::Noncopyable {
public:
    static T &getInstance();
private:
    GenericSingleton();
    ~GenericSingleton();
    static void init();
    static void destroy();
    static pthread_once_t control_;
    static T *instance_;
};
  
template <typename T>
T* GenericSingleton<T>::instance_ = NULL;
    
template <typename T>
pthread_once_t GenericSingleton<T>::control_ = PTHREAD_ONCE_INIT;
    
template <typename T>
T &GenericSingleton<T>::getInstance()
{
    pthread_once(&control_, &GenericSingleton<T>::init);
    return *instance_;
}

template <typename T>
void GenericSingleton<T>::init()
{
    instance_ = new T();
    atexit(&GenericSingleton<T>::destroy);
}
    
template <typename T>
GenericSingleton<T>::GenericSingleton()
{
    
}

template <typename T>
GenericSingleton<T>::~GenericSingleton()
{
    
}
    
template <typename T>
void GenericSingleton<T>::destroy()
{
    if (instance_) {
        delete instance_;
        instance_ = NULL;
    }
}

}



#endif /* GenericSingleton_h */
