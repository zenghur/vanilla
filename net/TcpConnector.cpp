//
//  TcpConnector.cpp
//  Vanilla
//
//  Created by ZengHongru on 16/6/5.
//
//

#include "TcpConnector.h"

using namespace vanilla;


void TcpConnector::canRead()
{
    
}

void TcpConnector::canWrite()
{
    
}

void TcpConnector::connect(std::string peerName, uint16_t port)
{
    
}


int TcpConnector::getConnectorFd()
{
    return socket_->getSocketFd();
}

