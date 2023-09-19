add_library(
    kv_common
    OBJECT
    murmurhash3.cpp
)

set(ALL_OBJECT_FILES
    ${ALL_OBJECT_FILES} $<TARGET_OBJECTS:kv_common>
    PARENT_SCOPE)