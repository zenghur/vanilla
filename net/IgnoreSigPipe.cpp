//
//  IgnoreSigPipe.cpp
//  Vanilla
//
//  Created by ZengHongru on 16/6/9.
//
//

#include <sys/signal.h>

#include "IgnoreSigPipe.h"
#include "GenericSingleton.h"

using namespace vanilla;

IgnoreSigPipe::IgnoreSigPipe()
{
    ::signal(SIGPIPE, SIG_IGN);
}

IgnoreSigPipe &ignoreSigPipe = GenericSingleton<IgnoreSigPipe>::getInstance();

