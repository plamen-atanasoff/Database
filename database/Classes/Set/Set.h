#pragma once

#include <iostream>
#include <vector>

// add dynamic shrink
class Set {
public:
    bool add(bool isNull);
    bool remove(size_t number);
    bool contains(size_t number) const;
private:
    std::vector<unsigned char> set;
    size_t maxNum = 0;

    size_t getBucketIndex(size_t number) const;
    unsigned char getMask(size_t number) const;

    friend std::ostream& operator<<(std::ostream& os, const Set& set);
};