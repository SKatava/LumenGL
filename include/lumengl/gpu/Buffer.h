// include/lumengl/gpu/Buffer.h
#pragma once
#include <glad/glad.h>
#include <span>

namespace lgl {

template<GLenum Target>
class Buffer {
public:
    Buffer()  { glGenBuffers(1, &m_id); }
    ~Buffer() { if (m_id) glDeleteBuffers(1, &m_id); }

    Buffer(const Buffer&)            = delete;
    Buffer& operator=(const Buffer&) = delete;

    Buffer(Buffer&& o) noexcept : m_id(o.m_id) { o.m_id = 0; }
    Buffer& operator=(Buffer&& o) noexcept {
        if (this != &o) {
            if (m_id) glDeleteBuffers(1, &m_id);
            m_id = o.m_id;
            o.m_id = 0;
        }
        return *this;
    }

    void bind()   const { glBindBuffer(Target, m_id); }
    void unbind() const { glBindBuffer(Target, 0);    }

    // Allocate + fill
    template<typename T>
    void upload(std::span<const T> data, GLenum usage = GL_STATIC_DRAW) {
        bind();
        glBufferData(Target, static_cast<GLsizeiptr>(data.size_bytes()),
                     data.data(), usage);
    }

    // Partial update — no reallocation
    template<typename T>
    void update(std::span<const T> data, GLintptr offsetBytes = 0) {
        bind();
        glBufferSubData(Target, offsetBytes,
                        static_cast<GLsizeiptr>(data.size_bytes()), data.data());
    }

    [[nodiscard]] GLuint id() const noexcept { return m_id; }

private:
    GLuint m_id {0};
};

using VBO = Buffer<GL_ARRAY_BUFFER>;
using EBO = Buffer<GL_ELEMENT_ARRAY_BUFFER>;

// VAO needs different GL calls
class VAO {
public:
    VAO()  { glGenVertexArrays(1, &m_id); }
    ~VAO() { if (m_id) glDeleteVertexArrays(1, &m_id); }

    VAO(const VAO&)            = delete;
    VAO& operator=(const VAO&) = delete;

    VAO(VAO&& o) noexcept : m_id(o.m_id) { o.m_id = 0; }
    VAO& operator=(VAO&& o) noexcept {
        if (this != &o) {
            if (m_id) glDeleteVertexArrays(1, &m_id);
            m_id = o.m_id;
            o.m_id = 0;
        }
        return *this;
    }

    void bind()   const { glBindVertexArray(m_id); }
    void unbind() const { glBindVertexArray(0);    }

    // Describe a vertex attribute
    void attrib(GLuint index, GLint size, GLenum type,
                GLsizei stride, GLsizei offsetBytes,
                GLboolean normalized = GL_FALSE) const
    {
        glEnableVertexAttribArray(index);
        glVertexAttribPointer(
            index, size, type, normalized,
            stride, reinterpret_cast<const void*>(
                static_cast<std::ptrdiff_t>(offsetBytes))
        );
    }

    // For instanced attributes
    void attribDivisor(GLuint index, GLuint divisor) const {
        glVertexAttribDivisor(index, divisor);
    }

    [[nodiscard]] GLuint id() const noexcept { return m_id; }

private:
    GLuint m_id {0};
};

} // namespace lgl
