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
    std::unique_ptr<Poller> poller = Poller::createPoller();
    TcpListener listener(poller.get());
    listener.listen("192.168.31.246", 15000);

    while (true) {
        poller->poll();
        usleep(50000);
    }
    return 0;
}

