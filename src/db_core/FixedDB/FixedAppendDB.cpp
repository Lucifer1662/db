#include "FixedAppendDB.h"
#include <cwchar>
#include "IO.h"

void FixedAppendDB::init(size_t size) {
    this->size = size;

    // this->head = 0;
    // io.writeAt(0, &this->head, sizeof(head));
    // this->head = 0;
    // io.readAt(0, &this->head, sizeof(head));
    // io.isEmpty();
    if (io.isEmpty()) {
        this->head = 0;
        io.writeAt(0, &this->head, sizeof(head));
    } else {
        io.readAt(0, &this->head, sizeof(head));
    }
}

size_t FixedAppendDB::append(const void* content) {
    io.writeAt(this->head + sizeof(head), content, size);
    head += size;
    io.writeAt(0, &this->head, sizeof(head));
    return head - size;
}

void FixedAppendDB::write(const void* content, size_t pos) {
    io.writeAt(pos + sizeof(head), content, size);
}

void FixedAppendDB::read(void* dst, size_t pos) const {
    io.readAt(pos + sizeof(head), dst, size);
}

bool FixedAppendDB::getHead(void* dst) const {
    if (head != 0) {
        read(dst, head - size);
        return true;
    }
    return false;
}

void FixedAppendDB::popHead() {
    if (head != 0) {
        head -= size;
    }
}

size_t FixedAppendDB::headPos() const { return head; }

bool FixedAppendDB::isEmpty() const { return head == 0; }
