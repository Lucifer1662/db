#pragma once
#include <optional>
#include "TreeNodeN.h"

class BPlusTreeIndexN;

class BTreeIterator
    : public std::iterator<std::input_iterator_tag,  // iterator_category
                           std::pair<Key, size_t>,   // value_type
                           std::pair<Key, size_t>,   // difference_type
                           const size_t*,            // pointer
                           std::pair<Key, size_t>    // reference
                           > {
    std::optional<Node> node;
    size_t at;
    const BPlusTreeIndexN& index;

   public:
    BTreeIterator(std::optional<Node> node, size_t at,
                  const BPlusTreeIndexN& index);

    BTreeIterator(const BTreeIterator&) = default;

    BTreeIterator& operator++();
    BTreeIterator operator++(int);
    bool operator==(BTreeIterator other) const;
    bool operator!=(BTreeIterator other) const;
    reference operator*() const;
};