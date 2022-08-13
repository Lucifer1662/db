#pragma once
#include <memory>


struct I_IO {
    virtual void writeAt(size_t pos, const void* content, size_t len) = 0;
    virtual void readAt(size_t pos, void* dst, size_t len) const = 0;
    virtual bool isEmpty() const = 0;
};

struct IO{
    std::shared_ptr<I_IO> io;

    IO( std::shared_ptr<I_IO> io): io(io) {}

    void writeAt(size_t pos, const void* content, size_t len){
        io->writeAt(pos, content, len);
    };

    void readAt(size_t pos, void* dst, size_t len) const {
        io->readAt(pos, dst, len);
    };

    bool isEmpty(){
        return io->isEmpty();
    }

};