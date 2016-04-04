//
//  ByteStream.hpp
//  Vanilla
//
//  Created by ZengHongru on 16/4/3.
//
//

#ifndef ByteStream_hpp
#define ByteStream_hpp

#include <iostream>
#include <vector>
#include <cassert>

#include "Endian.h"

// 头部预留headerSize_个字节用于网络通信协议ID，理论上可以支持2^64个协议，范围是0 － 2^64 - 1

namespace vanilla {

class ByteStream {
public:
    explicit ByteStream(std::size_t designatedContentSize = contentSize_);
public:
    size_t getReadableBytes();
    size_t getUnusedBytes();
public:
    char *getStartWritableAddr();
    const char *getStartWritableAddr() const;
    char *getStartReadableAddr();
    const char *getStartReadableAddr() const;
public:
    int64_t readInt64t();
    int32_t readInt32t();
    int16_t readInt16t();
    int8_t readInt8t();
    
    void writeInt64t(int64_t para);
    void writeInt32t(int32_t para);
    void writeInt16t(int16_t para);
    void writeInt8t(int8_t para);

private:
    template <typename T>
    T read(std::size_t nBytes);
    
    template <typename T>
    void write(T para);
    
    void guaranteeEnoughSpaceToWrite(int len);
private:
    std::vector<char> buffer_;
    std::size_t readIndex_;
    std::size_t writeIndex_;
    const static std::size_t headerSize_ = 8;
    const static std::size_t contentSize_ = 32 * 1024;
};
    
template <typename T>
T ByteStream::read(std::size_t nBytes)
{
    assert(getReadableBytes() >= nBytes);
    T temp = 0;
    std::copy(getStartReadableAddr(), getStartReadableAddr() + sizeof(T), reinterpret_cast<char*>(&temp));
    readIndex_ += nBytes;
    
    if (nBytes == sizeof(int64_t)) {
        return be64toh(temp);
    }
    else if (nBytes == sizeof(int32_t)) {
        return be32toh(temp);
    }
    else if (nBytes == sizeof(int16_t)) {
        return be16toh(temp);
    }
    else {
        return temp;
    }
}

template <typename T>
void ByteStream::write(T para)
{
    std::size_t len = sizeof(para);
    guaranteeEnoughSpaceToWrite(len);
    T temp = 0;
    if (len == sizeof(int64_t)) {
        temp = htobe64(para);
    }
    else if (len == sizeof(int32_t)) {
        temp = htobe32(para);
    }
    else if (len == sizeof(int16_t)) {
        temp = htobe16(para);
    }
    char *start = reinterpret_cast<char *>(&temp);
    std::copy(start, start + len, getStartWritableAddr());
    writeIndex_ += len;
}

}

#endif /* ByteStream_hpp */
