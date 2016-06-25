// copyright 2016 zenghur

#include "IOModule.h"

using vanilla::IOModule;

int main(void) {
    IOModule module;
    module.init("192.168.31.246", 16000);
    return 0;
}

