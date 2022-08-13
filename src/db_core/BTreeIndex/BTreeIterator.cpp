#include "BTreeIterator.h"
#include "BPlusTreeIndexN.h"
#include <optional>


BTreeIterator::BTreeIterator(std::optional<Node> node, size_t at,
                       const BPlusTreeIndexN& index)
    : node(node), at(at), index(index) {}

BTreeIterator& BTreeIterator::operator++() {
    if(node){
        if (at < node->data.size()) at++;

        if (at == node->data.size()) {
            if (node->next) {
                at = 0;
                node = index.child(*node->next);
            } else {
                node = {};
            }
        }
    }

    return *this;
}

BTreeIterator BTreeIterator::operator++(int) {
    BTreeIterator retval = *this;
    ++(*this);
    return retval;
}

bool BTreeIterator::operator==(BTreeIterator other) const {
    if (node.has_value()) {
        return node == other.node && at == other.at;
    }
    return node == other.node;
}
bool BTreeIterator::operator!=(BTreeIterator other) const {
    return !(*this == other);
}

BTreeIterator::reference BTreeIterator::operator*() const { return {node->intervals[at], node->data[at] }; }