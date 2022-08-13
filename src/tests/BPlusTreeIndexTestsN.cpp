#include <db_core.h>
#include <gtest/gtest.h>
#include <strstream>

#include <tuple>
#include <vector>

const size_t SEED = 100;

struct RNG {
    int operator()(int n) { return std::rand() / (1.0 + RAND_MAX) * n; }
};

auto genEntries(int from, int to) {
    std::vector<std::tuple<Key, size_t, bool>> entries;

    for (int i = from; i < to + 1; i++) {
        entries.push_back({{i}, i, rand() % 2 == 0});
    }

    std::srand(SEED);

    std::random_shuffle(entries.begin(), entries.end(), RNG());
    return entries;
}



TEST(BPlusTreeIndexTestsN, AddAndFind) {
    BPlusTreeIndexN index = createInMemomoryBTreeN();
    index.init();

    int start = 50;
    int end = 1000;

    auto entries = genEntries(start, end);


    for (auto& [key, pos, _] : entries) {
        index.add(key, pos);
    }

    for (auto& [key, pos, _] : entries) {
        ASSERT_EQ(index.find(key), std::make_optional(pos));
    }

    int i = start;
    for(auto pos : index){
        ASSERT_EQ(pos.second, i);
        ASSERT_EQ(pos.first.key, i);
        i ++;
    }

    ASSERT_EQ(end+1, i);


}


