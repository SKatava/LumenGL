# CMakeLists.txt
cmake_minimum_required(VERSION 3.22)
project(lumengl LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(external)

add_library(lumengl STATIC
    src/Context.cpp
    src/gpu/ShaderProgram.cpp
    src/gpu/Texture.cpp
    src/renderer/Mesh.cpp
    src/renderer/Material.cpp
    src/renderer/Camera.cpp
    src/renderer/Renderer.cpp
)

target_include_directories(lumengl PUBLIC include)

find_package(OpenGL REQUIRED)
target_link_libraries(lumengl
    PUBLIC
        glm::glm
        glfw
        glad
    PRIVATE
        stb
        OpenGL::GL
)

target_compile_options(lumengl PRIVATE
    $<$<CXX_COMPILER_ID:GNU,Clang>:-Wall -Wextra -Wpedantic>
    $<$<CXX_COMPILER_ID:MSVC>:/W4>
)

if(BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

option(BUILD_TESTS "Build tests" ON)
if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()
