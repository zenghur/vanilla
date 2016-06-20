// Copyright (c) 2016 zenghur

#ifndef NetworkEventType_h
#define NetworkEventType_h

namespace vanilla {

enum class NetworkEventType : int {
    ACCEPT,
    INCOMING_MESSAGE,
    CLOSE,
    CONNECT,
}
    
}

#endif /* NetworkEventType_h */
