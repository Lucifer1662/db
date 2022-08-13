#pragma once
#include <stddef.h>

#include <algorithm>
#include <sstream>
#include <tuple>
#include <vector>

#include <FixedDB.h>
#include "IntKey.h"
#include "TreeNodeN.h"
#include "BTreeIterator.h"


class BPlusTreeIndexN {
    using Key = IntKey;

   private:
    FixedDB data;

   public:
    BPlusTreeIndexN(FixedDB data) : data(data) {}

    void init() {
        data.init(Node::size());
        Node n;
        n.isLeaf = true;
        newNode(n);
    }

   
    Node child(size_t pos) const {
        static std::vector<char> content(Node::size());
        int r;
        data.read(content.data(), pos);
        auto n = Node::read(content.data(), r);
        n.myPos = pos;
        return n;
    }

   private:

    Node root() const { return child(0); }

    void newNode(Node& n) {
        static std::vector<char> content(Node::size());
        n.write(content.data());
        n.myPos = data.insert(content.data());
    }

    void save(Node& n) {
        static std::vector<char> content(Node::size());
        n.write(content.data());
        data.write(content.data(), n.myPos);
    }

   public:
    Node findNode(const Key& key, const Node& n) const {
        if (n.isLeaf) {
            return n;
        }

        auto size = n.intervals.size() - 1;
        for (size_t i = 0; i < size; ++i) {
            if (key <= n.intervals[i]) return findNode(key, child(n.data[i]));
        }

        return findNode(key, child(n.data[size]));
    }

    std::optional<size_t> find(const Key& key) const {
        auto leaf = findNode(key, root());

        for (size_t i = 0; i < leaf.childCount(); ++i) {
            if (key == leaf.intervals[i]) return leaf.data[i];
        }

        return {};
    }

   public:
    void add(const Key& key, size_t pos) {
        auto n = findNode(key, root());

        if (!n.isFull()) {
            auto size = n.intervals.size();

            bool inserted = false;
            for (size_t i = 0; i < size; ++i) {
                if (key < n.intervals[i]) {
                    n.insert(i, key, pos);
                    inserted = true;
                    break;
                }
            }
            
            if(!inserted){
                n.insert(size, key, pos);
            }

            save(n);
        } else {
            auto size = n.intervals.size();
            bool inserted = false;
            std::vector<Node> children(size);


            for (int i = 0; i < size; ++i) {
                Node& child = children[i];
                child.isLeaf = true;

                child.insert(0, n.intervals[i], n.data[i]);
                if ((key < n.intervals[i] || i == size-1 ) && !inserted) {
                    int at = key < n.intervals[i] ? 0 : 1;
                    child.insert(at, key, pos);
                    inserted = true;
                }

                newNode(child);
                n.data[i] = child.myPos;
            }

            if(n.prev){
                auto c = child(*n.prev);
                c.next = children.front().myPos;
                save(c);
            }

            if(n.next){
                auto c = child(*n.next);
                c.prev = children.back().myPos;
                save(c);
            }
            
            if(size >= 2){
                children.back().next = n.next;
            }
            
            if(size > 0){
                children.front().prev = n.prev;
            }

            for (int i = 0; i < size-1; i++) {
                children[i].next = children[i+1].myPos;
            }

            for (int i = 1; i < size; i++) {
                children[i].prev = children[i-1].myPos;
            }

            for(auto& c : children){
                save(c);
            }

            n.isLeaf = false;
            save(n);
        }

        assert(n.intervals.size() <= 5);
    }

    std::optional<size_t> remove(const Key& key) {
        auto n = findNode(key, root());

        for (size_t i = 0; i < n.size(); ++i) {
            if (key == n.intervals[i]) {
                n.remove(i);
                break;
            }
        }

        save(n);

        return {};
    }

    Node findLeftMostNode(const Node& n) const {
        if (n.isLeaf || n.data.size() == 0) {
            return n;
        }

        return findLeftMostNode(child(n.data[0]));
    }

    BTreeIterator begin() {
        auto leftNode = findLeftMostNode(root());
        return BTreeIterator(leftNode, 0, *this);
    }

    BTreeIterator end() {
        return BTreeIterator({}, 0, *this);
    }
};