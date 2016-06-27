// Copyright (c) 2016 zenghur

#include "Timestamp.h"

#include <sys/types.h>


#include "DateTime.h"

using vanilla::Timestamp;
using vanilla::DateTime;

Timestamp::Timestamp(timestamp_t value): epochTimeInMicroSeconds_{value} {
}

Timestamp::timestamp_t Timestamp::getTimestamp() {
  return epochTimeInMicroSeconds_;
}

vanilla::Timestamp::timestamp_t Timestamp::now() {
  struct timeval val;
  gettimeofday(&val, NULL);
  return DateTime::timevalToUs(val);
}

bool Timestamp::isValid() {
  return epochTimeInMicroSeconds_ != 0;
}

std::string Timestamp::getHumanReadableFormat() {
  char buf[50];
  struct tm datetime;
  time_t time = static_cast<time_t>(epochTimeInMicroSeconds_ / DateTime::kMicrosecondsPerSecond);
  localtime_r(&time, &datetime);
  strftime(buf, 50, "%Y-%m-%d %H:%M:%S", &datetime);
  return std::move(std::string(buf));
}
