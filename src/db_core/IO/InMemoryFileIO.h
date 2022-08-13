#pragma once
#include <algorithm>
#include <deque>
#include <memory>
#include "IO.h"

struct InMemoryFileIO : public I_IO {
    std::shared_ptr<std::deque<char>> data =
        std::make_shared<std::deque<char>>();
    
    bool mIsEmpty = true;

    InMemoryFileIO() = default;
    InMemoryFileIO(const InMemoryFileIO&) = default;
    InMemoryFileIO& operator=(const InMemoryFileIO&) = default;

    void writeAt(size_t pos, const void* content, size_t len) {
        mIsEmpty = false;
        if (pos == data->size()) {
            data->insert(data->begin() + pos, (const char*)content,
                         ((const char*)content) + len);
        } else {
            std::copy_n((const char*)content, len, data->begin() + pos);
        }
    }

    void readAt(size_t pos, void* dst, size_t len) const {
        std::copy_n(data->begin() + pos, len, (char*)dst);
    }

    static IO create(){
        return IO(std::make_shared<InMemoryFileIO>());
    }

    virtual bool isEmpty() const{
        return mIsEmpty;
    }
};