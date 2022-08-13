#pragma once
#include <algorithm>
#include <cstring>
#include <deque>
#include <IO.h>

class FixedAppendDB {
    IO io;
    size_t size;
    size_t head = 0;

   public:
    FixedAppendDB(IO io) : io(io) {}
    FixedAppendDB(const FixedAppendDB&) = default;
    FixedAppendDB& operator=(const FixedAppendDB&) = default;

    void init(size_t size);

    size_t append(const void* content);

    void write(const void* content, size_t pos);

    void read(void* dst, size_t pos) const;

    bool getHead(void* dst) const;

    void popHead();

    size_t headPos() const;

    bool isEmpty() const;

    
};