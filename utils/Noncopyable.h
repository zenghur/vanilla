// Copyright (c) 2016 zenghur

#ifndef UTILS_NONCOPYABLE_H_
#define UTILS_NONCOPYABLE_H_

namespace vanilla {
class Noncopyable {
 private:
   Noncopyable(const Noncopyable &);
   const Noncopyable &operator =(const Noncopyable &);
  
 protected:
   Noncopyable();
   ~Noncopyable();
};
}  // namespace vanilla

#endif  // UTILS_NONCOPYABLE_H_
