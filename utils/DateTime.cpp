//
//  DateTime.cpp
//  Vanilla
//
//  Created by ZengHongru on 16/4/15.
//
//

#include "DateTime.h"

#include <sys/types.h>

#include <cmath>


using namespace vanilla;

struct timespec DateTime::msToTimespec(int ms)
{
    struct timespec spec;
    spec.tv_sec = ms / 1000;
    spec.tv_nsec = (ms % 1000) * static_cast<int>(pow(10, 6));
    return spec;
}

struct timeval DateTime::msToTimeval(int ms)
{
    struct timeval val;
    val.tv_sec = ms / 1000;
    val.tv_usec = (ms % 1000) * static_cast<int>(pow(10, 3));
    return val;
}
