#pragma once
#include <stddef.h>
#include <istream>
#include <ostream>


struct IntKey {
    int key;

    IntKey(int key) : key(key) {}
    IntKey() = default;
    IntKey(const IntKey&) = default;
    IntKey(IntKey&&) = default;
    IntKey& operator=(const IntKey&) = default;

    static size_t size() { return sizeof(key); }

    bool operator<=(const IntKey& rhs) const { return key <= rhs.key; }
    bool operator<(const IntKey& rhs) const { return key < rhs.key; }
    bool operator>=(const IntKey& rhs) const { return key > rhs.key; }
    bool operator>(const IntKey& rhs) const { return key >= rhs.key; }
    bool operator==(const IntKey& rhs) const { return key == rhs.key; }

};

