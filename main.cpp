#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include "TcpSocket.h"
#include "SocketOption.h"
#include <vector>
#include "Poller.h"
#include "TcpListener.h"
#include "SocketOption.h"
#include "SessionIDDispatcher.h"
#include "Message.h"
#include "IOModule.h"


#include <iostream>

using namespace std;
using namespace vanilla;

int
main(void)
{
    IOModule module;
    module.init("127.0.0.1", 15050);
    return 0;
}

