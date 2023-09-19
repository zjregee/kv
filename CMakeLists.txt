cmake_minimum_required(VERSION 3.16.3)
project(KV)

set(CMAKE_CXX_STANDARD 17)

add_compile_options(-DCMAKE_BUILD_TYPE=Release)

set(KV_SRC_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/src/include)
set(KV_THIRD_PARTY_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/third_party/leveldb/include)

include_directories(${KV_SRC_INCLUDE_DIR} ${KV_THIRD_PARTY_INCLUDE_DIR})

add_subdirectory(src)
add_subdirectory(third_party)

add_executable(kv_correct_test ${PROJECT_SOURCE_DIR}/bench/correct_test.cpp)
add_executable(kv_single_thread_test ${PROJECT_SOURCE_DIR}/bench/single_thread_test.cpp)
add_executable(kv_multi_thread_test ${PROJECT_SOURCE_DIR}/bench/multi_thread_test.cpp)

target_link_libraries(kv_correct_test kv)
target_link_libraries(kv_single_thread_test kv)
target_link_libraries(kv_multi_thread_test kv)
