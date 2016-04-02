//
//  Singleton.h
//  Vanilla
//
//  Created by ZengHongru on 16/4/1.
//
//  In C++11, this is thread-safe method.

#ifndef Singleton_h
#define Singleton_h

#include "Noncopyable.h"

template <typename T>
class Singleton : private vanilla::Noncopyable {
public:
    static T &getInstance();
private:
    Singleton();
    ~Singleton();
};

template <typename T>
T &Singleton<T>::getInstance()
{
    static T instance;
    return instance;
}

template <typename T>
Singleton<T>::Singleton()
{
    
}

template <typename T>
Singleton<T>::~Singleton()
{
    
}


#endif /* Singleton_h */

