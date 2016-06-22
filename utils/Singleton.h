// Copyright (c) 2016 zenghur

#ifndef UTILS_SINGLETON_H_
#define UTILS_SINGLETON_H_

namespace vanilla {
template <typename T>
class Singleton {
 public:
   static T &getInstance();
  
 private:
   Singleton();
   ~Singleton();
};

template <typename T>
T &Singleton<T>::getInstance() {
  static T instance;
  return instance;
}

template <typename T>
Singleton<T>::Singleton() {
}

template <typename T>
Singleton<T>::~Singleton() {
}
}  // namespace vanilla


#endif  // UTILS_SINGLETON_H_

