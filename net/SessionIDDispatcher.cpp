// Copyright (c) 2016 zenghur

#include "SessionIDDispatcher.h"

#include <bitset>
#include <cassert>
#include <cmath>

using vanilla::SessionIDDispatcher;

// 24 + 8 + 32
SessionIDDispatcher::SessionType SessionIDDispatcher::getSessionId(int serverID, int channelID, int autoIncrementIndex) {
  SessionType s(iniValue);
  SessionType c(iniValue);
  SessionType a(iniValue);
  s |= serverID;
  s <<= (autoIncrementBits + channelBits);
  c |= channelID;
  c <<= autoIncrementBits;
  a |= autoIncrementIndex;
  return s | c | a;
}

SessionIDDispatcher::ID SessionIDDispatcher::getServerID(SessionType num) {
  return num >> (autoIncrementBits + channelBits);
}

SessionIDDispatcher::ID SessionIDDispatcher::getChannelID(SessionType num) {
  num >>= (autoIncrementBits);
  return static_cast<uint8_t>(num);
}

SessionIDDispatcher::ID SessionIDDispatcher::getAutoIncrementID(SessionType num) {
  return static_cast<ID>(num);
}



