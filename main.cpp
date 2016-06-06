#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include "TcpSocket.h"
#include "SocketOption.h"

#include <iostream>

using namespace std;
using namespace vanilla;

int
main(void)
{
    TcpSocket socket(TcpSocket::createListener("127.0.0.1", 15000));
    cout << SocketOption::getRcvBuf(socket.getSocketFd()) << endl;
    return 0;
}

