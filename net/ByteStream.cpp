//
//  ByteStream.cpp
//  Vanilla
//
//  Created by ZengHongru on 16/4/3.
//
//

#include "ByteStream.hpp"

#include <cassert>

#include "Endian.h"

using namespace vanilla;

ByteStream::ByteStream(std::size_t designatedContentSize): buffer_(headerSize_ + designatedContentSize),
                                                           readIndex_(headerSize_),
                                                           writeIndex_(headerSize_)
{
    
}

size_t ByteStream::getReadableBytes()
{
    assert(writeIndex_ >= readIndex_);
    return writeIndex_ - readIndex_;
}

size_t ByteStream::getUnusedBytes()
{
    return buffer_.size() - writeIndex_;
}

void ByteStream::guaranteeEnoughSpaceToWrite(int len)
{
    if (len > getUnusedBytes()) {
         buffer_.resize(writeIndex_ + len);
    }
}

void ByteStream::writeInt64t(int64_t para)
{
    write<int64_t>(para);
}

void ByteStream::writeInt32t(int32_t para)
{
    write<int32_t>(para);
}

void ByteStream::writeInt16t(int16_t para)
{
    write<int16_t>(para);
}

void ByteStream::writeInt8t(int8_t para)
{
    write<int8_t>(para);
}

int64_t ByteStream::readInt64t()
{
    return read<int64_t>(sizeof(int64_t));
}

int32_t ByteStream::readInt32t()
{
    return read<int32_t>(sizeof(int32_t));
}

int16_t ByteStream::readInt16t()
{
    return read<int16_t>(sizeof(int16_t));
}

int8_t ByteStream::readInt8t()
{
    return read<int8_t>(sizeof(int8_t));
}

char *ByteStream::getStartWritableAddr()
{
    return &*buffer_.begin() + writeIndex_;
}

const char *ByteStream::getStartWritableAddr() const
{
    return &*buffer_.begin() + writeIndex_;
}

char *ByteStream::getStartReadableAddr()
{
    return &*buffer_.begin() + readIndex_;
}

const char *ByteStream::getStartReadableAddr() const
{
    return &*buffer_.begin() + readIndex_;
}


