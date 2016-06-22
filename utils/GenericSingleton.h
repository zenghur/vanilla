// Copyright (c) 2016 zenghur

// Double-checked locking pattern(DCLP)的做法有问题。
// Scott Meyers and Andrei Alexandrescu对此有话要说！文章名叫C++ and the Perils of Double-Checked Locking。

#ifndef UTILS_GENERICSINGLETON_H_
#define UTILS_GENERICSINGLETON_H_

#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>

#include <cstdlib>

namespace vanilla {
template <typename T>
class GenericSingleton {
 public:
  static T &getInstance();
  
 private:
   GenericSingleton() = default;
   ~GenericSingleton() = default;
   GenericSingleton(const GenericSingleton &) = delete;
   GenericSingleton& operator =(const GenericSingleton &) = delete;
  
 private:
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
T &GenericSingleton<T>::getInstance() {
  pthread_once(&control_, &GenericSingleton<T>::init);
  return *instance_;
}

template <typename T>
void GenericSingleton<T>::init() {
  instance_ = new T();
  atexit(&GenericSingleton<T>::destroy);
}
  
template <typename T>
void GenericSingleton<T>::destroy() {
  if (instance_) {
    delete instance_;
    instance_ = NULL;
  }
}
}  // namespace vanilla

#endif  // UTILS_GENERICSINGLETON_H_
