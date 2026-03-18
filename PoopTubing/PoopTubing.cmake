add_library(PoopTubing
    PoopTubing/src/EntryPoint.hpp
    PoopTubing/src/EntryPoint.cpp

    PoopTubing/src/Application.hpp
    PoopTubing/src/Application.cpp

    PoopTubing/src/Core.hpp
)

target_link_libraries(PoopTubing PUBLIC
    glfw
    glm_math
    # imgui
    StbImplementation
    glad
    yamlcpp
)

target_include_directories(PoopTubing PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/PoopTubing/src
)

set_target_properties(PoopTubing PROPERTIES
    OUTPUT_NAME PoopTubing
    ARCHIVE_OUTPUT_DIRECTORY ${OUTPUT_DIR}/PoopTubing
    LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_DIR}/PoopTubing
    RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR}/PoopTubing
)

message("==== Config compile definition : ${CONFIG_COMPILE_DEFINITION} ====")

target_compile_definitions(PoopTubing PUBLIC
    "$<$<CONFIG:debug>:PT_LOGGER>"
    "$<$<CONFIG:debug>:PT_ASSERT>"

    "$<$<CONFIG:debug>:PT_DEBUG>"
    "$<$<CONFIG:release>:PT_RELEASE>"

    ${CONFIG_COMPILE_DEFINITION}
)
