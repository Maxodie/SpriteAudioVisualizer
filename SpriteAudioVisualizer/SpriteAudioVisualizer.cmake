add_library(SpriteAudioVisualizer
    SpriteAudioVisualizer/vendors/glad/glad/src/glad.c
    SpriteAudioVisualizer/vendors/stb/stb/stb_image.h

    SpriteAudioVisualizer/src/EntryPoint.hpp
    SpriteAudioVisualizer/src/EntryPoint.cpp

        SpriteAudioVisualizer/src/Application/Application.hpp
        SpriteAudioVisualizer/src/Application/Application.cpp
        SpriteAudioVisualizer/src/Application/LayerStack.hpp
        SpriteAudioVisualizer/src/Application/LayerStack.cpp

        SpriteAudioVisualizer/src/Utils/FileSystem.hpp
        SpriteAudioVisualizer/src/Utils/FileSystem.cpp
        SpriteAudioVisualizer/src/Utils/StringHelper.hpp

        SpriteAudioVisualizer/src/Window/Window.cpp
        SpriteAudioVisualizer/src/Window/Window.hpp
        SpriteAudioVisualizer/src/Window/GraphicsContext.cpp
        SpriteAudioVisualizer/src/Window/GraphicsContext.hpp

        SpriteAudioVisualizer/src/Event/Event.hpp
        SpriteAudioVisualizer/src/Event/WindowEvent.hpp

        SpriteAudioVisualizer/src/Renderer/RendererAPI.cpp
        SpriteAudioVisualizer/src/Renderer/RendererAPI.hpp
        SpriteAudioVisualizer/src/Renderer/OpenglGraphicsContext.cpp
        SpriteAudioVisualizer/src/Renderer/OpenglGraphicsContext.hpp
        SpriteAudioVisualizer/src/Renderer/Renderer.cpp
        SpriteAudioVisualizer/src/Renderer/Renderer.hpp
        SpriteAudioVisualizer/src/Renderer/RenderStructures.hpp
        SpriteAudioVisualizer/src/Renderer/Texture.cpp
        SpriteAudioVisualizer/src/Renderer/Texture.hpp
        SpriteAudioVisualizer/src/Renderer/Camera.cpp
        SpriteAudioVisualizer/src/Renderer/Camera.hpp
        SpriteAudioVisualizer/src/Renderer/Transform.hpp

        SpriteAudioVisualizer/src/Audio/Microphone.cpp
        SpriteAudioVisualizer/src/Audio/Microphone.hpp

    SpriteAudioVisualizer/src/Core.hpp

    SpriteAudioVisualizer/src/Log/Log.hpp
    SpriteAudioVisualizer/src/Log/Log.cpp
)

install(TARGETS SpriteAudioVisualizer LIBRARY COMPONENT portaudio)

target_link_libraries(SpriteAudioVisualizer PRIVATE
    glfw
    glm_math
    imgui
    yaml-cpp::yaml-cpp

    # portaudio
    ${CMAKE_CURRENT_SOURCE_DIR}/SpriteAudioVisualizer/vendors/portaudio/lib/.libs/portaudio.dll.lib
)

target_include_directories(SpriteAudioVisualizer PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/SpriteAudioVisualizer/src
    ${CMAKE_CURRENT_SOURCE_DIR}/SpriteAudioVisualizer/vendors/GLFW/glfw/include
    ${CMAKE_CURRENT_SOURCE_DIR}/SpriteAudioVisualizer/vendors/glad/glad/include
    ${CMAKE_CURRENT_SOURCE_DIR}/SpriteAudioVisualizer/vendors/imgui/imgui
    ${CMAKE_CURRENT_SOURCE_DIR}/SpriteAudioVisualizer/vendors/yamlcpp/yaml-cpp/include
    ${CMAKE_CURRENT_SOURCE_DIR}/SpriteAudioVisualizer/vendors/stb/stb
    ${CMAKE_CURRENT_SOURCE_DIR}/SpriteAudioVisualizer/vendors/portaudio/portaudio/include
)

if(CMAKE_BUILD_TYPE STREQUAL debug)
    set_target_properties(SpriteAudioVisualizer PROPERTIES
        OUTPUT_NAME SpriteAudioVisualizer
        ARCHIVE_OUTPUT_DIRECTORY ${OUTPUT_DIR}/SpriteAudioVisualizer/debug
        LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_DIR}/SpriteAudioVisualizer/debug
        RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR}/SpriteAudioVisualizer/debug
    )
else()
    set_target_properties(SpriteAudioVisualizer PROPERTIES
        OUTPUT_NAME SpriteAudioVisualizer
        ARCHIVE_OUTPUT_DIRECTORY ${OUTPUT_DIR}/SpriteAudioVisualizer/release
        LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_DIR}/SpriteAudioVisualizer/release
        RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR}/SpriteAudioVisualizer/release
    )
endif()

message("==== Config compile definition : ${CONFIG_COMPILE_DEFINITION} ====")

target_compile_definitions(SpriteAudioVisualizer PUBLIC
    "$<$<CONFIG:debug>:PT_LOGGER>"
    "$<$<CONFIG:debug>:PT_ASSERT>"

    "$<$<CONFIG:debug>:PT_DEBUG>"
    "$<$<CONFIG:release>:PT_RELEASE>"

    ${CONFIG_COMPILE_DEFINITION}
)
