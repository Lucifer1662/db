#pragma once
#include <string>
#include <vector>
#include <cstring>

struct Field {
    std::string name;
     enum Type {
            Int32,
            int64,
        } type;
        size_t size;
    size_t size;
    bool indexed;
};

struct RowInstance {
    std::vector<char> data;
    RowInstance(std::vector<char>&& data) : data(std::move(data)) {}
};

struct Row {
    std::vector<Field> fields;
    std::vector<size_t> offsets;
    size_t size = 0;
    Row(std::vector<Field>&& fields) : fields(std::move(fields)) {
        offsets.reserve(fields.size());
        for (auto& f : fields) {
            size += f.size;
        }
    }

    static void setInt32(char* r, int32_t i) { std::memcpy(r, &i, sizeof(i)); }

    void setInt32(RowInstance* r, size_t i, int32_t x) {
        setInt32(r->data.data() + offsets[i], x);
    }

    static int32_t getInt32(char* r){
        int32_t i;
        std::memcpy(r, &i, sizeof(i));
        return i;
    }

    int32 getInt32(RowInstance* r, size_t i) {
        return getInt32(r->data.data() + offsets[i]);
    }
    

    RowInstance instantiate() { return RowInstance(std::vector<char>(size)); }
    
};