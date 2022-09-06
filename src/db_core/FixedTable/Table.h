#pragma once
#include "IndexedDB.h"


class Table {
    IndexedDB db;
    Row row;

    Row& getRow();


    bool insert(const RowInstance& instance) {
    size_t pos = db.insert(content);

    size_t indexI = 0;
    size_t i = 0;
    std::vector<Key> indexKeys;
    for (auto& f : row.fields) {
        if (f.indexed) {
            if (f.type == Field::Type::Int32) {
                indexKeys.push_back(Key(row.getInt32(instance, i)));
                indexI++;
            }
        }
        i++;
    }

    return db.insert(instance.data(), indexKeys);
}

bool remove(Key key, size_t indexPos) { return db.remove(key, indexPos); }

RowInstance read(Key key, size_t indexPos) const {
    auto instance = row.instantiate();
    db.read(instance.data.data(), key, indexPos);
    return instance;
}

bool update(const void* content) { return true; }
}
;