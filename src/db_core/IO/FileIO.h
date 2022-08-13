#pragma once
#include <memory.h>

#include <fstream>

#include "IO.h"

struct FileIO : public I_IO {
    mutable std::fstream file;

    FileIO(std::fstream&& s) : file(std::move(s)) {}

    void writeAt(size_t pos, const void* content, size_t len) {
        file.seekp(pos);
        file.write((const char*)content, len);
        file.flush();
        if (file.bad()) {
            throw std::runtime_error("Failed to write");
        }
    }

    void readAt(size_t pos, void* dst, size_t len) const {
        file.seekg(pos);
        file.get((char*)dst, len);
        if (file.bad()) {
            throw std::runtime_error("Failed to read");
        }
    }

    static IO create(const std::string& name) {
        std::fstream file(name,
                          std::ios::in | std::ios::out | std::ios::binary);

        if (!file.is_open())
            file.open(name, std::ios::in | std::ios::out | std::ios::binary |
                                std::ios::trunc);

        return IO(std::make_shared<FileIO>(std::move(file)));
    }

    virtual bool isEmpty() const {
        file.seekg(0, std::ios::end);
        return file.tellg() == 0;
    }

    virtual ~FileIO() = default;
};