// Copyright (c) 2016 zenghur

#ifndef NET_BOSS_H_
#define NET_BOSS_H_

#include "ConcurrentQueue.h"
#include "Message.h"
#include "Thread.h"

namespace vanilla {

class IOModule;
  
class Boss {
 public:
   explicit Boss(IOModule *module);
   static void *loop(void *para);
   void start();
   void join();
   bool isProcessing();
   void setProcessing(bool flag);
   int pop_front(Message *item);
   bool push_back(Message *item);
   void sleep(int ms);
    
 private:
   Boss(const Boss &) = delete;
   Boss &operator = (const Boss &) = delete;
    
 private:
   bool processing_;
   IOModule *module_;
   ConcurrentQueue<Message> requestMessageQueue_;
   Thread thread_;
};
}  // namespace vanilla

#endif  // NET_BOSS_H_
