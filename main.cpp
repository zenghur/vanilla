// copyright 2016 zenghur

#include "IOModule.h"
#include "BlockingQueue.h"
#include "Timestamp.h"

#include <string>
#include <iostream>

using vanilla::IOModule;
using vanilla::BlockingQueue;
using vanilla::Timestamp;
using std::string;

int main(void) {
//    IOModule module;
//    module.init("192.168.31.246", 16000);
  vanilla::Timestamp ts(Timestamp::now());
  std::cout << ts.getHumanReadableFormat() << std::endl;
  
}

