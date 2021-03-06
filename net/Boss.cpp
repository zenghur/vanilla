// Copyright (c) 2016 zenghur

#include "Boss.h"

#include <sys/time.h>

#include <iostream>

#include "IOModule.h"

using vanilla::Boss;
using vanilla::IOModule;
using namespace std;

Boss::Boss(IOModule *module) : processing_(false),
                               module_(module) {
}

void *Boss::loop(void *para) {
  Boss *boss = reinterpret_cast<Boss*>(para);
  if (!boss) {
    return nullptr;
  }
  boss->setProcessing(true);
  while (boss->isProcessing()) {
    Message item;
    if (boss->pop_front(item) == -1) {
      boss->sleep(20);
      continue;
    } else {
      boss->getModule()->sendMessageToChannel(item);
    }
  }
  return boss;
}

void Boss::start() {
  thread_.start(Boss::loop, this);
}

void Boss::join() {
  thread_.join();
}

bool Boss::isProcessing() {
  return processing_;
}

void Boss::setProcessing(bool flag) {
  processing_ = flag;
}

int Boss::pop_front(Message &item) {
  return requestMessageQueue_.pop_front(item);
}

bool Boss::push_back(Message &item) {
  return requestMessageQueue_.push_back(item);
}

void Boss::sleep(int ms) {
  thread_.sleep(ms);
}

IOModule *Boss::getModule() {
  return module_;
}
