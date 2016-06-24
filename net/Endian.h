// Copyright (c) 2016 zenghur

#ifndef NET_ENDIAN_H_
#define NET_ENDIAN_H_

#ifdef __APPLE__
#include <libkern/OSByteOrder.h>

#define vanilla_htobe16(x) OSSwapHostToBigInt16(x)
#define vanilla_htole16(x) OSSwapHostToLittleInt16(x)
#define vanilla_be16toh(x) OSSwapBigToHostInt16(x)
#define vanilla_le16toh(x) OSSwapLittleToHostInt16(x)
#define vanilla_htobe32(x) OSSwapHostToBigInt32(x)
#define vanilla_htole32(x) OSSwapHostToLittleInt32(x)
#define vanilla_be32toh(x) OSSwapBigToHostInt32(x)
#define vanilla_le32toh(x) OSSwapLittleToHostInt32(x)
#define vanilla_htobe64(x) OSSwapHostToBigInt64(x)
#define vanilla_htole64(x) OSSwapHostToLittleInt64(x)
#define vanilla_be64toh(x) OSSwapBigToHostInt64(x)
#define vanilla_le64toh(x) OSSwapLittleToHostInt64(x)

#elif __linux__
#include <Endian.h>

#define vanilla_htobe16(x) htobe16(x)
#define vanilla_htole16(x) htole16(x)
#define vanilla_be16toh(x) be16toh(x)
#define vanilla_le16toh(x) le16toh(x)

#define vanilla_htobe32(x) htobe32(x)
#define vanilla_htole32(x) htole32(x)
#define vanilla_be32toh(x) be32toh(x)
#define vanilla_le32toh(x) le32toh(x)

#define vanilla_htobe64(x) htobe64(x)
#define vanilla_htole64(x) htole64(x)
#define vanilla_be64toh(x) be64toh(x)
#define vanilla_le64toh(x) le64toh(x)

#endif

#endif  // NET_ENDIAN_H_