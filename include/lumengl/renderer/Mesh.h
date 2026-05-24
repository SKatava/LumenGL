// include/lumengl/renderer/Mesh.h
#pragma once
#include <glad/glad.h>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <span>
#include <vector>
#include "lumengl/gpu/Buffer.h"

namespace lgl {

// Explicit, tightly packed. No hidden padding.
struct Vertex {
    glm::vec3 position;  // offset  0, size 12
    glm::vec3 normal;    // offset 12, size 12
    glm::vec2 uv;        // offset 24, size  8
                         // total: 32 bytes
};

static_assert(sizeof(Vertex) == 32, "Vertex layout changed — update attrib pointers");
static_assert(offsetof(Vertex, position) == 0);
static_assert(offsetof(Vertex, normal)   == 12);
static_assert(offsetof(Vertex, uv)       == 24);

class Mesh {
public:
    Mesh(std::span<const Vertex>   vertices,
         std::span<const uint32_t> indices,
         GLenum usage = GL_STATIC_DRAW);

    // Non-copyable — GPU data isn't trivially copyable
    Mesh(const Mesh&)            = delete;
    Mesh& operator=(const Mesh&) = delete;
    Mesh(Mesh&&)                 = default;
    Mesh& operator=(Mesh&&)      = default;

    // Update geometry without reallocating — caller ensures size fits
    void updateVertices(std::span<const Vertex> vertices);

    void bind()   const { m_vao.bind(); }
    void unbind() const { m_vao.unbind(); }

    [[nodiscard]] GLsizei indexCount() const noexcept { return m_indexCount; }

    // Factory helpers
    [[nodiscard]] static Mesh quad();
    [[nodiscard]] static Mesh cube();
    [[nodiscard]] static Mesh icosphere(int subdivisions = 3);
    [[nodiscard]] static Mesh uvsphere(int stacks = 32, int slices = 32);

private:
    VAO     m_vao;
    VBO     m_vbo;
    EBO     m_ebo;
    GLsizei m_indexCount {0};

    void setupAttribs() const;
};

} // namespace lgl
