// Copyright (c) 2016 zenghur

#ifndef __Vanilla__DateTime__
#define __Vanilla__DateTime__


#include <time.h>
#include <sys/time.h>


namespace vanilla {

class DateTime {
public:
    
    static struct timespec msToTimespec(int ms);
    static struct timeval msToTimeval(int ms);
    
};
    
}

#endif /* defined(__Vanilla__DateTime__) */
