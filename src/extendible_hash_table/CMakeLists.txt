add_library(
    kv_extendible_hash_table
    OBJECT
    bucket_page.cpp
    directory_page.cpp
    disk_extendible_hash_table.cpp
    directory_region.cpp
)

set(ALL_OBJECT_FILES
    ${ALL_OBJECT_FILES} $<TARGET_OBJECTS:kv_extendible_hash_table>
    PARENT_SCOPE)