#pragma once
#include <stddef.h>

#include <algorithm>
#include <cassert>
#include <sstream>
#include <tuple>
#include <vector>

#include "../FixedDB/FixedDB.h"
#include "IntKey.h"
using Key = IntKey;


template <int NUM>
struct NodeData {
    bool isLeaf;

    size_t intervals_size;
    size_t data_size;
    std::array<Key, NUM> intervals;
    std::array<size_t, NUM> data;

    std::optional<size_t> prev;
    std::optional<size_t> next;

    NodeData() = default;
    NodeData(bool isLeaf, size_t intervals_size, size_t data_size,
             const std::vector<Key>& intervals, const std::vector<size_t>& data,
             std::optional<size_t> prev, std::optional<size_t> next)
        : isLeaf(isLeaf),
          intervals_size(intervals_size),
          data_size(data_size),
          prev(prev),
          next(next) {
        std::copy(intervals.begin(), intervals.end(), this->intervals.begin());
        std::copy(data.begin(), data.end(), this->data.begin());
    }
};

using Key = IntKey;
struct Node {
    const static size_t NUM = 5;

    size_t myPos = 0;
    bool isLeaf;

    std::vector<Key> intervals;
    std::vector<size_t> data;

    std::optional<size_t> prev;
    std::optional<size_t> next;

    Node() {
        intervals.reserve(NUM);
        data.reserve(NUM);
    }

    static constexpr size_t size() { return sizeof(NodeData<NUM>); }

    size_t childCount(){ return data.size(); }

    void write(void* dst) {
        NodeData<NUM> d(isLeaf, intervals.size(), data.size(), intervals, data,
                        prev, next);
        memcpy(dst, &d, sizeof(d));
    }

    static Node read(const void* src, int& amountRead) {
        Node n;
        NodeData<NUM> data;
        memcpy(&data, src, sizeof(data));
        n.isLeaf = data.isLeaf;
        n.prev = data.prev;
        n.next = data.next;
        n.intervals =
            std::vector<Key>(data.intervals.begin(),
                             data.intervals.begin() + data.intervals_size);
        n.data = std::vector<size_t>(data.data.begin(),
                                     data.data.begin() + data.data_size);

        return n;
    }

    bool operator==(Node other) const { return myPos == other.myPos; }

    bool isFull() { return NUM == data.size(); }

    void insert(size_t i, Key key, size_t pos) {
        intervals.insert(intervals.begin() + i, key);
        data.insert(data.begin() + i, pos);
    }

    void remove(size_t i) {
        intervals.erase(intervals.begin() + i);
        data.erase(data.begin() + i);
    }
};