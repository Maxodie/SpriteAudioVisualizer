# set(CMAKE_SUPPRESS_REGENERATION true)
# set_property(GLOBAL PROPERTY USE_FOLDERS ON)

project (imgui LANGUAGES CXX)

set(ImguiFolder ${CMAKE_CURRENT_SOURCE_DIR}/SpriteAudioVisualizer/vendors/imgui/imgui)

file(GLOB main_sources ${ImguiFolder}/*.cpp)
file(GLOB main_headers ${ImguiFolder}/*.hpp)

add_library(imgui STATIC
    ${main_sources}
    ${main_headers}

    ${ImguiFolder}/backends/imgui_impl_glfw.cpp
    ${ImguiFolder}/backends/imgui_impl_glfw.h

    ${ImguiFolder}/backends/imgui_impl_opengl3.cpp
    ${ImguiFolder}/backends/imgui_impl_opengl3.h
    ${ImguiFolder}/backends/imgui_impl_opengl3_loader.h
)

set_target_properties(imgui PROPERTIES
    OUTPUT_NAME imgui
    ARCHIVE_OUTPUT_DIRECTORY ${OUTPUT_DIR}/imgui
    LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_DIR}/imgui
    RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR}/imgui
)

target_include_directories(imgui PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/SpriteAudioVisualizer/vendors/imgui/imgui
    ${CMAKE_CURRENT_SOURCE_DIR}/SpriteAudioVisualizer/vendors/GLFW/glfw/include
)

# foreach(source IN LISTS source_list)
#     source_group("Source" FILES "${source}")
# endforeach()
