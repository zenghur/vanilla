#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include "TcpSocket.h"
#include "SocketOption.h"
#include <vector>
#include "Poller.h"
#include "TcpListener.h"


#include <iostream>

using namespace std;
using namespace vanilla;

int
main(void)
{
    TcpListener listener;
    listener.listen("192.168.31.246", 15000);
    std::unique_ptr<Poller> poller = Poller::createPoller();
    poller->addFd(listener.getListenerFd(), PollerEvent::POLLER_IN, &listener);
    while (true) {
        poller->poll();
        usleep(50000);
    }
    return 0;
}

