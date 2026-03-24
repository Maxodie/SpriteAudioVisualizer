cmake_minimum_required(VERSION 3.30)
project(SpriteAudioVisualizer VERSION 1.0.0)
cmake_policy(SET CMP0072 NEW)

option(CMAKE_EXPORT_COMPILE_COMMANDS "allow the creatation of an compile_commands.json file" ON)
option(GIT_SUBMODULE "allow git submodule auto update" ON)

if(CMAKE_EXPORT_COMPILE_COMMANDS)
    message("==== Create .clangd file to store 'CompilationDatabase: build/${CMAKE_BUILD_TYPE}' ====")
    file(WRITE ".clangd"
        "CompileFlags:
            CompilationDatabase: build/${CMAKE_BUILD_TYPE}"
    )
endif()

if(GIT_SUBMODULE)
    find_package(Git REQUIRED)
    message(STATUS "Submodule update")
    execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
                    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                    RESULT_VARIABLE GIT_SUBMO_RESULT)
    if(NOT GIT_SUBMO_RESULT EQUAL 0)
        message(FATAL_ERROR "git submodule update --init --recursive failed with ${GIT_SUBMO_RESULT}")
    endif()
endif()

set(BIN_OUTPUT_DIR "/bin/${CMAKE_SYSTEM_NAME}")
set(OUTPUT_DIR "${CMAKE_CURRENT_SOURCE_DIR}${BIN_OUTPUT_DIR}")

if(COMPILE_CONFIG_BUILD)
    set(CONFIG_COMPILE_DEFINITION PT_BUILD)
else()
    set(CONFIG_COMPILE_DEFINITION PT_EDITOR)
endif()

include(SpriteAudioVisualizer/SpriteAudioVisualizer.cmake)
include(SpriteAudioVisualizerEditor/SpriteAudioVisualizerEditor.cmake)
include(SpriteAudioVisualizer/vendors/GLFW/GLFW.cmake)
include(SpriteAudioVisualizer/vendors/glm/glm.cmake)
include(SpriteAudioVisualizer/vendors/imgui/imgui.cmake)
include(SpriteAudioVisualizer/vendors/glad/glad.cmake)
add_subdirectory(SpriteAudioVisualizer/vendors/yamlcpp/yaml-cpp)

# find_package(portaudio REQUIRED)
# add_subdirectory(SpriteAudioVisualizer/vendors/portaudio/portaudio EXCLUDE_FROM_ALL)

unset(COMPILE_CONFIG_BUILD CACHE)
