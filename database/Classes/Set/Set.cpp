#include "Set.h"

namespace {
	constexpr unsigned short bitsInByte = 8;
}

bool Set::add(bool isNull)
{
    if (maxNum >= set.size() * bitsInByte)
    {
        set.push_back(0);
    }

    if (!isNull) {
        size_t bucketIndex = getBucketIndex(maxNum);
        unsigned char mask = getMask(maxNum);
        set[bucketIndex] |= mask;
    }
    
    maxNum++;
    return true;
}

bool Set::flip(size_t number)
{
    if (number >= maxNum)
    {
        return false;
    }

    size_t bucketIndex = getBucketIndex(number);
    unsigned char mask = getMask(number);
    set[bucketIndex] ^= mask;
    return true;
}

bool Set::contains(size_t number) const
{
    if (number >= maxNum)
    {
        return false;
    }

    size_t bucketIndex = getBucketIndex(number);
    unsigned char mask = getMask(number);
    return (mask & set[bucketIndex]);
}

void Set::clear()
{
    set.clear();
    maxNum = 0;
}

size_t Set::getBucketIndex(size_t number) const
{
	return number / bitsInByte;
}

unsigned char Set::getMask(size_t number) const
{
    unsigned short indInBucket = number % bitsInByte;
    unsigned char mask = 1<<indInBucket;
    return mask;
}

std::ostream& operator<<(std::ostream& os, const Set& set)
{
    size_t bucketsCount = set.set.size();
    unsigned char last = 1 << (bitsInByte - 1);

    os << "{ ";
    for (int i = 0; i < bucketsCount; i++)
    {
        for (unsigned char j = 1; j <= last && j != 0; j <<= 1)
        {
            os << (set.set[i] & j ? 1 : 0) << " ";
        }
    }
    os << "} ";
    return os;
}
