//
//  Socket.hpp
//  Vanilla
//
//  Created by ZengHongru on 16/6/5.
//
//

#ifndef Socket_h
#define Socket_h

#include <stdint.h>

#include <string>
#include <vector>

#include "Noncopyable.h"

namespace vanilla {

class TcpSocket : private vanilla::Noncopyable {
public:
    static const int SND_BUF = 64 * 1024;
    static const int RCV_BUF = 64 * 1024;
public:
    explicit TcpSocket(int fd = -1);
    ~TcpSocket();
    void close();
    
    int nonBlockSend(char *data, size_t len);
    int nonBlockRecv(char *data, size_t len);
    
    int blockSend(char *data, size_t len);
    int blockRecv(char *data, size_t len);
    
    int getSocketFd();
    
    void setNonBlock();
public:
    static TcpSocket* createListener(std::string ip, uint16_t port);
    static TcpSocket* createConnector(std::string ip, uint16_t port);
private:
    bool isNonBlocking_;
    int sockfd_;
    
    // ring buffer
    std::vector<char> sendBuf_;
    int sendBufStartIndex_;
    int sendLen_;
    
    std::vector<char> recvBuf_;
    int recvBufStartIndex_;
    int recvLen_;
};
    
}

#endif /* Socket_h */
