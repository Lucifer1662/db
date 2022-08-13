#pragma once
// #include <gtest/gtest.h>
// #include <db_core.h>

// #include <tuple>
// #include <vector>

// const size_t SEED = 100;

// struct RNG {
//     int operator()(int n) { return std::rand() / (1.0 + RAND_MAX) * n; }
// };

// auto genEntries(int from, int to) {
//     std::vector<std::tuple<Key, size_t, bool>> entries;

//     for (int i = from; i < to + 1; i++) {
//         entries.push_back({{i}, i, rand() % 2 == 0});
//     }

//     std::srand(SEED);

//     std::random_shuffle(entries.begin(), entries.end(), RNG());
//     return entries;
// }

// TEST(BPlusTreeIndexTest, AddAndFindOne) {
//     BPlusTreeIndex index = createInMemomoryFixedDB();
//     index.init();

//     auto entries = genEntries(5, 6);

//     for (auto& [key, pos, _] : entries) {
//         index.add(key, pos);
//     }

//     for (auto& [key, pos, _] : entries) {
//         ASSERT_EQ(index.find(key), std::make_optional(pos));
//     }
// }

// TEST(BPlusTreeIndexTest, AddAndFind) {
//     BPlusTreeIndex index = createInMemomoryFixedDB();
//     index.init();

//     auto entries = genEntries(50, 100);

//     for (auto& [key, pos, _] : entries) {
//         index.add(key, pos);
//     }

//     for (auto& [key, pos, _] : entries) {
//         ASSERT_EQ(index.find(key), std::make_optional(pos));
//     }
// }


// TEST(BPlusTreeIndexTest, AddAndIterate) {
//     BPlusTreeIndex index = createInMemomoryFixedDB();
//     index.init();

//     auto entries = genEntries(50, 54);

//     for (auto& [key, pos, _] : entries) {
//         index.add(key, pos);
//     }

//     auto it = index.begin();
//     auto end = index.end();

//     size_t current = 50;
//     for(;it != end; it++, current++){
//         auto pos = *it;
//         ASSERT_EQ(current, pos);
//     } 

// }

// TEST(BPlusTreeIndexTest, AddAndDelete) {
//     BPlusTreeIndex index = createInMemomoryFixedDB();
//     index.init();

//     auto entries = genEntries(50, 100);

//     for (auto& [key, pos, _] : entries) {
//         index.add(key, pos);
//     }

//     for (auto& [key, pos, _] : entries) {
//         ASSERT_EQ(index.find(key), std::make_optional(pos));
//     }

//     for (auto& [key, pos, remove] : entries) {
//         if (remove) {
//             index.remove(key);
//         }
//     }

//     for (auto& [key, pos, remove] : entries) {
//         if (remove) {
//             ASSERT_EQ(index.find(key), std::optional<size_t>());
//         } else {
//             ASSERT_EQ(index.find(key), std::make_optional(pos));
//         }
//     }
// }
