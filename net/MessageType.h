// Copyright (c) 2016 zenghur

#ifndef NET_MESSAGETYPE_H_
#define NET_MESSAGETYPE_H_

namespace vanilla {
enum MessageType : int {
    NET_MSG,
    NET_MSG_ACCEPT,
    NET_MSG_CLOSE,
    NET_MSG_CONNECT,
    TIMER_MSG,
};
}  // namespace vanilla

#endif  // NET_MESSAGETYPE_H_
