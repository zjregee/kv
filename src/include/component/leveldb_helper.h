#pragma once

#include <string>

#include "leveldb/db.h"
#include "leveldb/options.h"

namespace kv {

class LevelDBHelper {
public:
    LevelDBHelper(const std::string &database_name) {
        leveldb::Options options;
        options.create_if_missing = true;
        leveldb::Status status = leveldb::DB::Open(options, database_name, &db_);
        if (!status.ok()) {
            perror("open database error");
            exit(1);
        }
    }

    ~LevelDBHelper() {
        delete db_;
    }

    auto Insert(const std::string &key, const std::string &value) -> bool {
        leveldb::WriteOptions write_options;
        write_options.sync = true;
        leveldb::Status status = db_->Put(write_options, key, value);
        return status.ok();
    }

    auto GetValue(const std::string &key, std::string &value) -> bool {
        leveldb::ReadOptions read_options;
        leveldb::Status status = db_->Get(read_options, key, &value);
        return status.ok();
    }

    auto Remove(const std::string &key) -> bool {
        leveldb::WriteOptions write_options;
        write_options.sync = true;
        leveldb::Status status = db_->Delete(write_options, key);
        return status.ok();
    }

private:
    leveldb::DB *db_;
};

}
