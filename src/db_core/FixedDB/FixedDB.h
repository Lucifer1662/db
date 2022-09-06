#pragma once
#include "FixedAppendDB.h"

struct FixedDB {
    FixedAppendDB data;
    FixedAppendDB deletes;

    


    FixedDB(IO dataIO, IO deletesIO) : data(dataIO), deletes(deletesIO) {}
    FixedDB(const FixedDB&) = default;
    FixedDB& operator=(const FixedDB&) = default;

    void init(size_t size);

    size_t insert(const char* content);

    void remove(size_t pos);

    void read(void* dst, size_t pos) const;

    void write(const void* content, size_t pos);

    bool isEmpty(){
        return data.isEmpty();
    }
};
