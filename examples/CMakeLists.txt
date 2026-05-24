# examples/CMakeLists.txt

# ─────────────────────────────────────────────────────────────
# Helper function — avoids repeating boilerplate per example.
# Usage: lgl_example(NAME 01_triangle SOURCES main.cpp)
# ─────────────────────────────────────────────────────────────
function(lgl_example)
    cmake_parse_arguments(EX "" "NAME" "SOURCES" ${ARGN})

    if(NOT EX_NAME)
        message(FATAL_ERROR "lgl_example requires NAME")
    endif()
    if(NOT EX_SOURCES)
        message(FATAL_ERROR "lgl_example requires SOURCES")
    endif()

    add_executable(${EX_NAME} ${EX_SOURCES})

    target_link_libraries(${EX_NAME} PRIVATE lumengl glfw)

    # Copy the example's local shaders/assets into the build dir next to the exe.
    # Structure: examples/01_triangle/shaders/*.vert|.frag
    set(SHADER_SRC "${CMAKE_CURRENT_SOURCE_DIR}/${EX_NAME}/shaders")
    set(SHADER_DST "$<TARGET_FILE_DIR:${EX_NAME}>/shaders")

    if(EXISTS "${SHADER_SRC}")
        add_custom_command(TARGET ${EX_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory
                "${SHADER_SRC}"
                "${SHADER_DST}"
            COMMENT "[${EX_NAME}] Copying shaders to build dir"
        )
    endif()

    # Same for assets (textures, models)
    set(ASSET_SRC "${CMAKE_CURRENT_SOURCE_DIR}/${EX_NAME}/assets")
    set(ASSET_DST "$<TARGET_FILE_DIR:${EX_NAME}>/assets")

    if(EXISTS "${ASSET_SRC}")
        add_custom_command(TARGET ${EX_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory
                "${ASSET_SRC}"
                "${ASSET_DST}"
            COMMENT "[${EX_NAME}] Copying assets to build dir"
        )
    endif()

endfunction()

# ─────────────────────────────────────────────────────────────
# Examples — add one line per example
# ─────────────────────────────────────────────────────────────
lgl_example(NAME 01_triangle  SOURCES 01_triangle/main.cpp)
lgl_example(NAME 02_cube      SOURCES 02_cube/main.cpp)
lgl_example(NAME 03_sphere  SOURCES 03_sphere/main.cpp)
#lgl_example(NAME 04_instanced SOURCES 04_instanced/main.cpp)
