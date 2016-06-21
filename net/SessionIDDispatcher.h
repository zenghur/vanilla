// Copyright (c) 2016 zenghur

#ifndef NET_SESSIONIDDISPATCHER_H_
#define NET_SESSIONIDDISPATCHER_H_

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
    
}  // namespace vanilla

#endif  // NET_SESSIONIDDISPATCHER_H_
