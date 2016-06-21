// Copyright (c) 2016 zenghur

#include "IgnoreSigPipe.h"

#include <sys/signal.h>

#include "GenericSingleton.h"

using vanilla::IgnoreSigPipe;
using vanilla::GenericSingleton;

IgnoreSigPipe::IgnoreSigPipe() {
    ::signal(SIGPIPE, SIG_IGN);
}

IgnoreSigPipe &ignoreSigPipe = GenericSingleton<IgnoreSigPipe>::getInstance();

