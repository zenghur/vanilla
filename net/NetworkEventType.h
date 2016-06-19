//
//  NetworkEventType.hpp
//  Vanilla
//
//  Created by ZengHongru on 16/6/19.
//
//

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
