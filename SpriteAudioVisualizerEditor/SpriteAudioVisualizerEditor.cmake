add_executable(SpriteAudioVisualizerEditor

    SpriteAudioVisualizerEditor/src/Editor.cpp
    SpriteAudioVisualizerEditor/src/Editor.hpp
    SpriteAudioVisualizerEditor/src/MicSelection.cpp
    SpriteAudioVisualizerEditor/src/MicSelection.hpp
)

target_link_libraries(SpriteAudioVisualizerEditor PRIVATE
    SpriteAudioVisualizer
    imgui
    glm_math
)

target_include_directories(SpriteAudioVisualizerEditor PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/SpriteAudioVisualizer/src
    ${CMAKE_CURRENT_SOURCE_DIR}/SpriteAudioVisualizerEditor/src
    ${CMAKE_CURRENT_SOURCE_DIR}/SpriteAudioVisualizer/vendors/portaudio/portaudio/include
    ${CMAKE_CURRENT_SOURCE_DIR}/SpriteAudioVisualizer/vendors/imgui/imgui
)

if(CMAKE_BUILD_TYPE STREQUAL debug)
    set_target_properties(SpriteAudioVisualizerEditor PROPERTIES
        OUTPUT_NAME SpriteAudioVisualizerEditor
        ARCHIVE_OUTPUT_DIRECTORY ${OUTPUT_DIR}/SpriteAudioVisualizerEditor/debug
        LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_DIR}/SpriteAudioVisualizerEditor/debug
        RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR}/SpriteAudioVisualizerEditor/debug
    )
else()
    set_target_properties(SpriteAudioVisualizerEditor PROPERTIES
        OUTPUT_NAME SpriteAudioVisualizerEditor
        ARCHIVE_OUTPUT_DIRECTORY ${OUTPUT_DIR}/SpriteAudioVisualizerEditor/release
        LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_DIR}/SpriteAudioVisualizerEditor/release
        RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR}/SpriteAudioVisualizerEditor/release
    )
endif()

if(CONFIG_COMPILE_DEFINITION STREQUAL PT_EDITOR)
    target_compile_definitions(SpriteAudioVisualizerEditor PRIVATE
        PT_EDITOR
    )
else()

    target_compile_definitions(SpriteAudioVisualizerEditor PRIVATE
        PT_BUILD
    )
endif()
