// Copyright (c) 2016 zenghur

#ifndef  UTILS_ERROR_H_
#define  UTILS_ERROR_H_

#include <stdio.h>

#include <string>

namespace vanilla {
void printError(std::string reason = "");
void threadError(int status);
}  // namespace vanilla

#endif  // UTILS_ERROR_H_
