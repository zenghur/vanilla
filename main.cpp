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
#include "PassiveMessageReactor.h"
#include "Message.h"


#include <iostream>

using namespace std;
using namespace vanilla;

int
main(void)
{
    
    std::unique_ptr<char[]> data(new char[10]);
    std::unique_ptr<char[]> datum;
    datum = std::move(data);
    return 0;
}

