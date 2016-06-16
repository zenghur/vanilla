//
//  SessionIDDispatcher.hpp
//  Vanilla
//
//  Created by ZengHongru on 16/6/11.
//
//

#ifndef SessionIDDispatcher_h
#define SessionIDDispatcher_h

#include <stdint.h>

namespace vanilla {

class SessionIDDispatcher {
public:
    typedef uint64_t SessionType;
    typedef uint32_t ID;
    static SessionType getSessionId(int serverID, int channelID, int autoIncrementIndex);
    static ID getServerID(SessionType num);
    static ID getChannelID(SessionType num);
    static ID getAutoIncrementID(SessionType num);
private:
    static const int serverBits = 24;
    static const int channelBits = 8;
    static const int autoIncrementBits = 32;
    static const int allBits = 64;
    static const SessionType iniValue = 0x0000000000000000;
    
};
    
}



#endif /* SessionIDDispatcher_h */
