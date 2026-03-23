cmake_minimum_required(VERSION 3.30)
project(PoopTubing VERSION 1.0.0)
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

include(PoopTubing/PoopTubing.cmake)
include(PoopTubingEditor/PoopTubingEditor.cmake)
include(PoopTubing/vendors/GLFW/GLFW.cmake)
include(PoopTubing/vendors/glm/glm.cmake)
include(PoopTubing/vendors/imgui/imgui.cmake)
include(PoopTubing/vendors/glad/glad.cmake)
add_subdirectory(PoopTubing/vendors/yamlcpp/yaml-cpp)

# find_package(portaudio REQUIRED)
# add_subdirectory(PoopTubing/vendors/portaudio/portaudio EXCLUDE_FROM_ALL)

unset(COMPILE_CONFIG_BUILD CACHE)
