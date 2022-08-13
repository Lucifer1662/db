#include <gtest/gtest.h>
#include <InMemoryFileIO.h>

TEST(InMemoryFileIOTests, WriteAndRead1AtStart) {
    InMemoryFileIO io;

    auto data = "Hello There";
    auto len = strlen(data) + 1;

    io.writeAt(0, data, len);

    char actual[20];
    io.readAt(0, actual, len);

    ASSERT_EQ(std::string(actual), std::string(data));
}

TEST(InMemoryFileIOTests, WriteAndReadMultipleAtStart) {
    InMemoryFileIO io;
    size_t pos = 0;

    std::vector<const char*> datas;
    datas.push_back("Hello There");
    datas.push_back("General Kenoby");
    datas.push_back("Why Hello");

    for (const char* data : datas) {
        auto len = strlen(data) + 1;
        io.writeAt(pos, data, len);
        pos += len;
    }

    pos = 0;
    // for(size_t i = 0; i < datas.size(); i++){
    for (const char* data : datas) {
        // const char* data = datas[i];
        char actual[20];
        auto len = strlen(data) + 1;
        io.readAt(pos, actual, len);
        pos += len;
        ASSERT_EQ(std::string(actual), std::string(data));
    }
}

TEST(InMemoryFileIOTests, Reasign) {
    InMemoryFileIO io;

    {
        auto data = "Hello There";
        auto len = strlen(data) + 1;

        io.writeAt(0, data, len);

        char actual[20];
        io.readAt(0, actual, len);
        ASSERT_EQ(std::string(actual), std::string(data));
    }

    {
        auto data = "General Kenoby Woby";
        auto len = strlen(data) + 1;

        io.writeAt(0, data, len);

        char actual[30];
        io.readAt(0, actual, len);
        ASSERT_EQ(std::string(actual), std::string(data));
    }
}
