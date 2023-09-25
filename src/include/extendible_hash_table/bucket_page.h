#pragma once

#include <string>

#include "common/page.h"

namespace kv {

class HashTableBucketPage: public Page {
public:
    auto InitWith() {
        
    }

    auto GetValueWithKeyValueSize(const std::string &key, std::string &result, size_t key_size, size_t value_size) -> bool;
    auto InsertWithKeyValueSize() -> bool;


private:
    size_t bucket_key_size_;
    size_t bucket_value_size_;
    size_t bucket_entry_size_;
    size_t bucket_array_size_;
    size_t bucket_array_offset_;

    auto IsOccupied() -> bool;
    void SetOccupied();
};

}