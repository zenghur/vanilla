// Copyright (c) 2016 zenghur

#ifndef NET_IOMODULE_H_
#define NET_IOMODULE_H_

#include <vector>
#include <string>

#include "Channel.h"
#include "Boss.h"
#include "TcpListener.h"

namespace vanilla {
    
class Channel;
    
class IOModule {
 public:
   IOModule() = default;
   void init(std::string ip, uint16_t port);
   void start();
   bool sendMessageToBoss(Message *message);
  
 private:
   IOModule(const IOModule &) = delete;
   IOModule& operator = (const IOModule &) = delete;
   std::shared_ptr<TcpListener> listener_;
   std::vector<std::shared_ptr<Channel> > channels_;
   std::shared_ptr<Boss> boss_;
  
 private:
   static const int NUM_OF_POLLERS = 2;
};
}  // namespace vanilla

#endif  // NET_IOMODULE_H_
