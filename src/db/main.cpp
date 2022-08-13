#include <db_core.h>

#include <iostream>

void findAndPrint(BPlusTreeIndexN& index, Key key) {
    auto ret = index.find(key);

    if (ret) {
        std::cout << *ret << std::endl;
    } else {
        std::cout << "Not found" << std::endl;
    }
}

int main() {
    // auto io = FileIO::create("test1.data");
    // auto s = "Hello World";
    // io.writeAt(5, s, strlen(s));

    // char w[30];
    // io.readAt(5, w, strlen(s));

    // return 0;
    BPlusTreeIndexN index = createFileBTreeN("test2");
    index.init();

    std::vector<std::tuple<Key, size_t, bool>> entries;

    for (size_t i = 50; i < 53; i++) {
        // entries.push_back({{i}, i, rand() % 2 == 0});
    }

    std::random_shuffle(entries.begin(), entries.end());

    // for (auto& [key, pos, _] : entries) {
    //     std::cout << pos << std::endl;
    //     index.add(key, pos);
    // }

    // for (auto& [key, pos, _] : entries) {
    //     std::cout << pos << std::endl;
    //     auto ret = index.find(key);
    //     if (!ret || *ret != pos) {
    //         std::cout << "Fail" << std::endl;
    //         ret = index.find(key);
    //     }
    // }

    for (auto& [key, pos, remove] : entries) {
        if (remove) {
            std::cout << pos << std::endl;
            index.remove(key);
        }
    }

    for (auto& [key, pos, remove] : entries) {
        std::cout << pos << std::endl;
        auto ret = index.find(key);
        if (remove) {
            if (ret) {
                std::cout << "Fail" << std::endl;
                ret = index.find(key);
            }
        } else {
            if (!ret || *ret != pos) {
                std::cout << "Fail" << std::endl;
                ret = index.find(key);
            }
        }
    }

    return 0;
}