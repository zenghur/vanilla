// Copyright (c) 2016 zenghur

#include <sys/signal.h>

#include "IgnoreSigPipe.h"
#include "GenericSingleton.h"

using namespace vanilla;

IgnoreSigPipe::IgnoreSigPipe()
{
    ::signal(SIGPIPE, SIG_IGN);
}

IgnoreSigPipe &ignoreSigPipe = GenericSingleton<IgnoreSigPipe>::getInstance();

