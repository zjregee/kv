#pragma once

#include <string>

namespace kv {

class LevelDBHelper {
public:
    LevelDBHelper() {

    }

    ~LevelDBHelper() {

    }

    auto Insert(const std::string &key, const std::string &value) -> bool {

    }

    auto GetValue(const std::string &key, std::string &value) -> bool {

    }

    auto Remove(const std::string &key) -> bool {

    }

private:

};

}