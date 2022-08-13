#pragma once
#ifndef BLAH
#define BLAH

#include "BTreeIndex/BPlusTreeIndexN.h"
#include "FixedDB/FixedDB.h"
#include "InMemoryFileIO.h"
#include "FileIO.h"


FixedDB createInMemomoryFixedDB() {
    return FixedDB(InMemoryFileIO::create(), InMemoryFileIO::create());
}

FixedDB createFileFixedDB(const std::string& name) {
    return FixedDB(FileIO::create(name+".data"), FileIO::create(name+".index"));
}


BPlusTreeIndexN createInMemomoryBTreeN() {
    return BPlusTreeIndexN(createInMemomoryFixedDB());
}

BPlusTreeIndexN createFileBTreeN(const std::string& name) {
    return BPlusTreeIndexN(createFileFixedDB(name));
}

#endif