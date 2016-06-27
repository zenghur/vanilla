// Copyright (c) 2016 zenghur

#ifndef UTILS_DATETIME_H_
#define UTILS_DATETIME_H_

#include <time.h>
#include <sys/time.h>
#include <stdint.h>

namespace vanilla {
class DateTime {
 public:
   static struct timespec msToTimespec(int ms);
   static struct timeval msToTimeval(int ms);
   static uint64_t timevalToUs(struct timeval &val);
  
 public:
   static constexpr int kNanosecondsPerSecond = 1000 * 1000 * 1000;
   static constexpr int kMicrosecondsPerSecond = 1000 * 1000;
   static constexpr int kMillisecondsPerSecond = 1000;

 public:
   static const int kSecondsPerDay = 24 * 60 * 60;
   static const int kSecondsPerHour = 60 * 60;
   static const int kSecondsPerMinute = 60;
};
}  // namespace vanilla

#endif  // UTILS_DATETIME_H_
