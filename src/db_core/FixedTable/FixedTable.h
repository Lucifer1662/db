#pragma once
#include <BPlusTreeIndexN.h>
#include <FixedDB/FixedDB.h>

#include <vector>




struct KeyExtractor{
    size_t pos;

    Key extract(char* content){
        return IntKey(content+pos);
    }

};


struct TableDB {
    std::vector<BPlusTreeIndexN> index;

    std::vector<
    FixedDB db;

    bool insert(const char* content, std::vector<Key> indexKeys) {
        size_t pos = db.insert(content);
        for (size_t i = 0; i < index.size(); i++) {
            index[i].add(pos, indexKeys[i]);
        }

        return true;
    }

    bool remove(Key key, size_t indexPos) {
        if (indexPos < index.size()) {
            auto pos = indexs[indexPos].find(key);
            db.remove(pos);
        } else {
            return false;
        }
        return true;
    }

    bool read(void* dst, Key key, size_t indexPos) const {
        if (indexPos < index.size()) {
            auto pos = indexs[indexPos].find(key);
            db.read(dst, pos);
        } else {
            return false;
        }
        return true;
    }

    bool update(const void* content, Key key, size_t indexPos,
                std::vector<std::pair<Key, Key>> indexKeys) {
        if (indexPos < index.size()) {
            auto pos = indexs[indexPos].find(key);
            db.update(content, pos);

            for (size_t i = 0; i < index.size(); i++) {
                if(indexKeys[i].first != indexKeys[i].second){
                    index[i].remove(indexKeys[i].first);
                    index[i].add(pos, indexKeys[i],second);
                }
            }

        } else {
            return false;
        }
        return true;
    }
};