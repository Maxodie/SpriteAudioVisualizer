if(CONFIG_COMPILE_DEFINITION STREQUAL PT_EDITOR)
    message("==== Compile Editor ====")
    add_executable(PoopTubingEditor
        PoopTubingEditor/src/Editor.cpp
    )

    target_link_libraries(PoopTubingEditor PRIVATE
        PoopTubing
        glm_math
    )

    target_include_directories(PoopTubingEditor PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/PoopTubing/src
        ${CMAKE_CURRENT_SOURCE_DIR}/PoopTubingEditor/src
        ${CMAKE_CURRENT_SOURCE_DIR}/PoopTubing/vendors/portaudio/portaudio/include
    )

    if(CMAKE_BUILD_TYPE STREQUAL debug)
        set_target_properties(PoopTubingEditor PROPERTIES
            OUTPUT_NAME PoopTubingEditor
            ARCHIVE_OUTPUT_DIRECTORY ${OUTPUT_DIR}/PoopTubingEditor/debug
            LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_DIR}/PoopTubingEditor/debug
            RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR}/PoopTubingEditor/debug
        )
    else()
        set_target_properties(PoopTubingEditor PROPERTIES
            OUTPUT_NAME PoopTubingEditor
            ARCHIVE_OUTPUT_DIRECTORY ${OUTPUT_DIR}/PoopTubingEditor/release
            LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_DIR}/PoopTubingEditor/release
            RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR}/PoopTubingEditor/release
        )
    endif()
endif()
