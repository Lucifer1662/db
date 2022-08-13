#include "FixedDB.h"



void FixedDB::init(size_t size) {
    data.init(size);
    deletes.init(sizeof(size_t));
}



size_t FixedDB::insert(const char* content) {
    if (deletes.isEmpty()) {
        return data.append(content);
    } else {
        size_t pos;
        deletes.getHead((char*)&pos);
        deletes.popHead();
        data.write(content, pos);
        return pos;
    }
}



void FixedDB::remove(size_t pos) {
    if (pos == data.headPos()) {
        data.popHead();
    } else {
        deletes.append(&pos);
    }
}



void FixedDB::read(void* dst, size_t pos) const { data.read(dst, pos); }



void FixedDB::write(const void* content, size_t pos) { data.write(content, pos); }

