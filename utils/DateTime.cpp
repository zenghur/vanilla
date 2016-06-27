// Copyright (c) 2016 zenghur

#include "DateTime.h"

#include <sys/types.h>

#include <cmath>

using vanilla::DateTime;

struct timespec DateTime::msToTimespec(int ms) {
  struct timespec spec;
  spec.tv_sec = ms / 1000;
  spec.tv_nsec = (ms % 1000) * static_cast<int>(pow(10, 6));
  return spec;
}

struct timeval DateTime::msToTimeval(int ms) {
  struct timeval val;
  val.tv_sec = ms / 1000;
  val.tv_usec = (ms % 1000) * static_cast<int>(pow(10, 3));
  return val;
}

uint64_t DateTime::timevalToUs(struct timeval &val) {
  return val.tv_sec * kMicrosecondsPerSecond + val.tv_usec;
}
