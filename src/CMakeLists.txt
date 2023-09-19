add_subdirectory(common)

add_library(kv STATIC ${ALL_OBJECT_FILES})

set(KV_LIBS
    kv_common
)

target_link_libraries(kv ${KV_LIBS})

target_include_directories(
    kv PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)