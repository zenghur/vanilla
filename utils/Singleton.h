// Copyright (c) 2016 zenghur

#ifndef Singleton_h
#define Singleton_h

#include "Noncopyable.h"

namespace vanilla {
    
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
    
}


#endif /* Singleton_h */

