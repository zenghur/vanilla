// Copyright (c) 2016 zenghur

#ifndef NET_BYTESTREAM_H_
#define NET_BYTESTREAM_H_

#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

#include "Endian.h"

// 头部预留headerSize_个字节

namespace vanilla {

class ByteStream {
 public:
   explicit ByteStream(std::size_t designatedContentSize = contentSize_);
   size_t getReadableBytes();
   size_t getUnusedBytes();
   char *getStartWritableAddr();
   const char *getStartWritableAddr() const;
   char *getStartReadableAddr();
   const char *getStartReadableAddr() const;
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
   static const std::size_t headerSize_ = 8;
   static const std::size_t contentSize_ = 12;
};
  
template <typename T>
T ByteStream::read(std::size_t nBytes) {
  assert(getReadableBytes() >= nBytes);
  T temp = 0;
  std::copy(getStartReadableAddr(), getStartReadableAddr() + sizeof(T), reinterpret_cast<char*>(&temp));
  readIndex_ += nBytes;
  if (nBytes == sizeof(int64_t)) {
    return vanilla_be64toh(temp);
  } else if (nBytes == sizeof(int32_t)) {
    return vanilla_be32toh(temp);
  } else if (nBytes == sizeof(int16_t)) {
    return vanilla_be16toh(temp);
  } else {
    return temp;
  }
}

template <typename T>
void ByteStream::write(T para) {
  std::size_t len = sizeof(para);
  guaranteeEnoughSpaceToWrite(len);
  T temp = 0;
  if (len == sizeof(int64_t)) {
    temp = vanilla_htobe64(para);
  } else if (len == sizeof(int32_t)) {
    temp = vanilla_htobe32(para);
  } else if (len == sizeof(int16_t)) {
    temp = vanilla_htobe16(para);
  }
  char *start = reinterpret_cast<char *>(&temp);
  std::copy(start, start + len, getStartWritableAddr());
  writeIndex_ += len;
}

}  // namespace vanilla

#endif  // NET_BYTESTREAM_H_
