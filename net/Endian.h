// Copyright (c) 2016 zenghur

#ifndef NET_ENDIAN_H_
#define NET_ENDIAN_H_

#ifdef __APPLE__
#include <libkern/OSByteOrder.h>

#define htobe16(x) OSSwapHostToBigInt16(x)
#define htole16(x) OSSwapHostToLittleInt16(x)
#define be16toh(x) OSSwapBigToHostInt16(x)
#define le16toh(x) OSSwapLittleToHostInt16(x)
#define htobe32(x) OSSwapHostToBigInt32(x)
#define htole32(x) OSSwapHostToLittleInt32(x)
#define be32toh(x) OSSwapBigToHostInt32(x)
#define le32toh(x) OSSwapLittleToHostInt32(x)
#define htobe64(x) OSSwapHostToBigInt64(x)
#define htole64(x) OSSwapHostToLittleInt64(x)
#define be64toh(x) OSSwapBigToHostInt64(x)
#define le64toh(x) OSSwapLittleToHostInt64(x)

#elif __linux__
#include <Endian.h>

#define htobe16(x) htobe16(x)
#define htole16(x) htole16(x)
#define be16toh(x) be16toh(x)
#define le16toh(x) le16toh(x)

#define htobe32(x) htobe32(x)
#define htole32(x) htole32(x)
#define be32toh(x) be32toh(x)
#define le32toh(x) le32toh(x)

#define htobe64(x) htobe64(x)
#define htole64(x) htole64(x)
#define be64toh(x) be64toh(x)
#define le64toh(x) le64toh(x)

#endif

#endif  // NET_ENDIAN_H_