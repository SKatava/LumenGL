cmake_minimum_required(VERSION 3.31.1)

project(renderer LANGUAGES C CXX)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

#Glad from source
add_library(glad STATIC external/glad/src/glad.c)
target_include_directories(glad PUBLIC external/glad/include)

#Stb
add_library(stb STATIC external/stb/src/stb_image.cpp)
target_include_directories(stb PUBLIC external/stb/include)

#library 
add_library(renderer STATIC
    src/renderer/VAO.cpp
    src/renderer/VBO.cpp
    src/renderer/EBO.cpp
    src/renderer/Shader_program.cpp
    src/renderer/Shader.cpp
    src/renderer/Logger.cpp
    src/renderer/Renderer.cpp
    src/renderer/Mesh.cpp
    src/renderer/Material.cpp
    src/renderer/Scene.cpp
    src/renderer/Texture.cpp
    src/renderer/Camera.cpp
)

target_include_directories(renderer
    PUBLIC
        include
    PRIVATE
        src
)

#link glad
target_link_libraries(renderer PUBLIC glad)

#link stb
target_link_libraries(renderer PUBLIC stb)

#link OpenGL
find_package(OpenGL REQUIRED)
target_link_libraries(renderer PUBLIC OpenGL::GL)

#link OpenGL mathematics
find_package(glm CONFIG REQUIRED)
target_link_libraries(renderer PRIVATE glm::glm)


#Enable errors
target_compile_options(renderer PRIVATE -Wall -Wextra -Wpedantic)

#examples subdir
option(BUILD_EXAMPLES "Build example applications" ON)

if (BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()
