add_library(glad
    PoopTubing/vendors/glad/glad/src/glad.c

    PoopTubing/vendors/glad/glad/include/glad/glad.h
    PoopTubing/vendors/glad/glad/include/KHR/khrplatform.h
)

target_link_libraries(glad PRIVATE
    glfw
)

target_compile_options(glad PRIVATE
    -std=c23
    -o3
)

set_target_properties(glad PROPERTIES
    OUTPUT_NAME glad
    ARCHIVE_OUTPUT_DIRECTORY ${OUTPUT_DIR}/glad
    LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_DIR}/glad
    RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR}/glad
)

target_include_directories(glad PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/PoopTubing/vendors/glad/glad/include
)
