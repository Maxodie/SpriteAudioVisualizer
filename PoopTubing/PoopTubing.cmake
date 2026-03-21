add_library(PoopTubing
    PoopTubing/vendors/glad/glad/src/glad.c
    PoopTubing/vendors/stb/stb/stb_image.h

    PoopTubing/src/EntryPoint.hpp
    PoopTubing/src/EntryPoint.cpp

        PoopTubing/src/Application/Application.hpp
        PoopTubing/src/Application/Application.cpp
        PoopTubing/src/Application/LayerStack.hpp
        PoopTubing/src/Application/LayerStack.cpp

        PoopTubing/src/Utils/FileSystem.hpp
        PoopTubing/src/Utils/FileSystem.cpp
        PoopTubing/src/Utils/StringHelper.hpp

        PoopTubing/src/Window/Window.cpp
        PoopTubing/src/Window/Window.hpp
        PoopTubing/src/Window/GraphicsContext.cpp
        PoopTubing/src/Window/GraphicsContext.hpp

        PoopTubing/src/Event/Event.hpp
        PoopTubing/src/Event/WindowEvent.hpp

        PoopTubing/src/Renderer/RendererAPI.cpp
        PoopTubing/src/Renderer/RendererAPI.hpp
        PoopTubing/src/Renderer/OpenglGraphicsContext.cpp
        PoopTubing/src/Renderer/OpenglGraphicsContext.hpp
        PoopTubing/src/Renderer/Renderer.cpp
        PoopTubing/src/Renderer/Renderer.hpp
        PoopTubing/src/Renderer/RenderStructures.hpp
        PoopTubing/src/Renderer/Texture.cpp
        PoopTubing/src/Renderer/Texture.hpp
        PoopTubing/src/Renderer/Camera.cpp
        PoopTubing/src/Renderer/Camera.hpp
        PoopTubing/src/Renderer/Transform.hpp

    PoopTubing/src/Core.hpp

    PoopTubing/src/Log/Log.hpp
    PoopTubing/src/Log/Log.cpp
)

target_link_libraries(PoopTubing PRIVATE
    glfw
    glm_math
    imgui
    yaml-cpp::yaml-cpp
)

target_include_directories(PoopTubing PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/PoopTubing/src
    ${CMAKE_CURRENT_SOURCE_DIR}/PoopTubing/vendors/GLFW/glfw/include
    ${CMAKE_CURRENT_SOURCE_DIR}/PoopTubing/vendors/glad/glad/include
    ${CMAKE_CURRENT_SOURCE_DIR}/PoopTubing/vendors/imgui/imgui
    ${CMAKE_CURRENT_SOURCE_DIR}/PoopTubing/vendors/yamlcpp/yaml-cpp/include
    ${CMAKE_CURRENT_SOURCE_DIR}/PoopTubing/vendors/stb/stb
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
