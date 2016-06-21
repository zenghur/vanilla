// Copyright (c) 2016 zenghur

#ifndef UTILS_DATETIME_H_
#define UTILS_DATETIME_H_

#include <time.h>
#include <sys/time.h>

namespace vanilla {
class DateTime {
 public:
  static struct timespec msToTimespec(int ms);
  static struct timeval msToTimeval(int ms);
};
}  // namespace vanilla

#endif  // UTILS_DATETIME_H_
