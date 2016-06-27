// Copyright (c) 2016 zenghur

#ifndef UTILS_TIMESTAMP_H_
#define UTILS_TIMESTAMP_H_

#include <stdint.h>
#include <sys/time.h>

#include <string>

namespace vanilla {
class Timestamp {
 public:
   typedef uint64_t timestamp_t;
   explicit Timestamp(timestamp_t value = 0);
   timestamp_t getTimestamp();
   std::string getHumanReadableFormat();
   static timestamp_t now();
   bool isValid();
  
 private:
   timestamp_t epochTimeInMicroSeconds_;  // resolution: microsecond
};
  
}  // namespace vanilla

#endif  // UTILS_TIMESTAMP_H_
