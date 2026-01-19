cmake_minimum_required(VERSION 3.31.1)

project(renderer LANGUAGES C CXX)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(NAME LumenGL)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

#Glad from source
add_library(glad STATIC external/glad/src/glad.c)
target_include_directories(glad PUBLIC external/glad/include)

#Stb
add_library(stb STATIC external/stb/src/stb_image.cpp)
target_include_directories(stb PUBLIC external/stb/include)

#library 
add_library(${NAME} STATIC
    src/LumenGL/VAO.cpp
    src/LumenGL/VBO.cpp
    src/LumenGL/EBO.cpp
    src/LumenGL/ShaderProgram.cpp
    src/LumenGL/Shader.cpp
    src/LumenGL/Logger.cpp
    src/LumenGL/Renderer.cpp
    src/LumenGL/Mesh.cpp
    src/LumenGL/Material.cpp
    src/LumenGL/Texture.cpp
    src/LumenGL/Camera.cpp
    src/LumenGL/Transform.cpp
    src/LumenGL/Scene.cpp
    src/LumenGL/RenderObjectBuilder.cpp
)

target_include_directories(${NAME}
    PUBLIC
        include
    PRIVATE
        src
)

#link glad
target_link_libraries(${NAME} PUBLIC glad)

#link stb
target_link_libraries(${NAME} PUBLIC stb)

#link OpenGL
find_package(OpenGL REQUIRED)
target_link_libraries(${NAME} PUBLIC OpenGL::GL)

#link OpenGL mathematics
find_package(glm CONFIG REQUIRED)
target_link_libraries(${NAME} PRIVATE glm::glm)


#Enable errors
target_compile_options(${NAME} PRIVATE -Wall -Wextra -Wpedantic)

#examples subdir
option(BUILD_EXAMPLES "Build example applications" ON)

if (BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()
