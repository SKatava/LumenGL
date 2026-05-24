// include/lumengl/gpu/ShaderProgram.h
#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string>
#include "lumengl/util/Result.h"

namespace lgl {

class ShaderProgram {
public:
    [[nodiscard]]
    static Result<ShaderProgram> fromFiles(
        const std::string& vertPath,
        const std::string& fragPath
    );

    [[nodiscard]]
    static Result<ShaderProgram> fromSource(
        const std::string& vertSrc,
        const std::string& fragSrc
    );

    ~ShaderProgram() { if (m_id) glDeleteProgram(m_id); }

    ShaderProgram(const ShaderProgram&)            = delete;
    ShaderProgram& operator=(const ShaderProgram&) = delete;

    ShaderProgram(ShaderProgram&& o) noexcept : m_id(o.m_id) { o.m_id = 0; }
    ShaderProgram& operator=(ShaderProgram&& o) noexcept {
        if (this != &o) {
            if (m_id) glDeleteProgram(m_id);
            m_id = o.m_id;
            o.m_id = 0;
        }
        return *this;
    }

    void use() const { glUseProgram(m_id); }

    // Uniform setters — assert location found in debug, silently skip in release
    void setInt  (const char* name, int v)                const;
    void setFloat(const char* name, float v)              const;
    void setBool (const char* name, bool v)               const;
    void setVec2 (const char* name, const glm::vec2& v)   const;
    void setVec3 (const char* name, const glm::vec3& v)   const;
    void setVec4 (const char* name, const glm::vec4& v)   const;
    void setMat3 (const char* name, const glm::mat3& v)   const;
    void setMat4 (const char* name, const glm::mat4& v)   const;

    [[nodiscard]] GLuint id() const noexcept { return m_id; }

private:
    explicit ShaderProgram(GLuint id) : m_id(id) {}

    [[nodiscard]]
    static Result<GLuint> compileStage(GLenum type, const std::string& src);

    [[nodiscard]]
    static GLint location(GLuint program, const char* name);

    GLuint m_id {0};
};

} // namespace lgl
