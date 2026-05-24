# LumenGL

A lightweight OpenGL rendering library written in C++23.

## Features
- RAII GPU object wrappers (VAO, VBO, EBO, Texture, ShaderProgram)
- Blinn-Phong lighting with multi-light support
- Icosphere and UV sphere generation with correct UV seam handling
- Submit/flush renderer with shader-sorted draw calls
- Error handling via Result<T> without exceptions

## Dependencies
Fetched automatically via CMake FetchContent:
- GLFW 3.4
- GLM 1.0.1
- STB Image
- GLAD (OpenGL 4.6 core, pre-generated)

## Build
```bash
mkdir build && cd build
cmake .. -DBUILD_EXAMPLES=ON
cmake --build . -j$(nproc)
```

## Examples
| Example | Demonstrates |
|---|---|
| 01_triangle | Basic pipeline, VAO/VBO, shader |
| 02_cube | 3D transforms, texture mapping, lighting |
| 03_sphere | Icosphere generation, planet shading |
