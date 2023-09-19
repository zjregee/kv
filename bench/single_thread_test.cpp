#include <iostream>
#include <chrono>
#include <string>
#include <vector>
#include <random>

#include "component/leveldb_helper.h"

int main(int argc, char* argv[]) {
    size_t data_num = 2000000;
    size_t key_size = 64;
    size_t value_size = 64;

    if (argc < 3) {
        data_num = 2000000;
        key_size = 64;
        value_size = 64;
    } else {
        
    }

    std::vector<std::string> random_keys;
    std::vector<std::vector<uint8_t>> random_values;
    random_keys.reserve(data_num);
    random_values.reserve(data_num);

    {
        const std::string charset = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
        std::random_device rd;
        std::mt19937 generator(rd());
        std::uniform_int_distribution<int> distribution(0, charset.size() - 1);

        for (int i = 0; i < data_num; i++) {
            std::string random_key;
            random_key.reserve(key_size);
            for (int j = 0; j < key_size; j++) {
                random_key.push_back(charset[distribution(generator)]);
            }
            random_keys.push_back(random_key);
        }
    }

    {
        std::random_device rd;
        std::mt19937 generator(rd());
        std::uniform_int_distribution<int> distribution(0, 255);

        for (int i = 0; i < data_num; i++) {
            std::vector<uint8_t> random_value;
            random_value.reserve(value_size);
            for (size_t j = 0; j < value_size; j++) {
                random_value.push_back(static_cast<uint8_t>(distribution(generator)));
            }
            random_values.push_back(random_value);
        }
    }



    {
        auto start_time = std::chrono::high_resolution_clock::now();
        auto end_time = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
        std::cout << "程序执行时间：" << duration.count() << "ms" << std::endl;
    }

    return 0;
}
