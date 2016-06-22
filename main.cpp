// copyright 2016 zenghur

#include "IOModule.h"

using vanilla::IOModule;

int main(void) {
    IOModule module;
    module.init("127.0.0.1", 15050);
    return 0;
}

