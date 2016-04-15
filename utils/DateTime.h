//
//  DateTime.h
//  Vanilla
//
//  Created by ZengHongru on 16/4/15.
//
//

#ifndef __Vanilla__DateTime__
#define __Vanilla__DateTime__


#include <time.h>


namespace vanilla {

class DateTime {
public:
    
    static struct timespec msToTimespec(int ms);
    
};
    
}

#endif /* defined(__Vanilla__DateTime__) */
