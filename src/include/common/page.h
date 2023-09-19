#pragma once

#include <string>
#include <cstring>

namespace KV {

static const size_t PAGE_SIZE = 4096;
static const int INVALID_PAGE_ID = -1;

class Page {
public:
    Page() {
        data_ = new char[PAGE_SIZE];
        ResetMemory();
    }

    ~Page() { delete[] data_; }

    auto GetData() -> char* { return data_; }

private:
    void ResetMemory() { memset(data_, 0, PAGE_SIZE); }
    char* data_;
};

}
