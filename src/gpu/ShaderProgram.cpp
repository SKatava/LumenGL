#include "lumengl/gpu/ShaderProgram.h"
#include <glm/gtc/type_ptr.hpp>
#include <fstream>
#include <sstream>
#include <cassert>

namespace lgl {

static std::string readFile(const std::string& path) {
    std::ifstream f(path);
    if (!f.is_open()) return "";
    std::ostringstream ss;
    ss << f.rdbuf();
    return ss.str();
}

Result<ShaderProgram> ShaderProgram::fromFiles(
    const std::string& vertPath, const std::string& fragPath)
{
    const std::string vertSrc = readFile(vertPath);
    const std::string fragSrc = readFile(fragPath);

    if (vertSrc.empty())
        return Result<ShaderProgram>::err("Could not read vertex shader: " + vertPath);
    if (fragSrc.empty())
        return Result<ShaderProgram>::err("Could not read fragment shader: " + fragPath);

    return fromSource(vertSrc, fragSrc);
}

Result<ShaderProgram> ShaderProgram::fromSource(
    const std::string& vertSrc, const std::string& fragSrc)
{
    auto vert = compileStage(GL_VERTEX_SHADER, vertSrc);
    if (vert.isErr()) return Result<ShaderProgram>::err(vert.error());

    auto frag = compileStage(GL_FRAGMENT_SHADER, fragSrc);
    if (frag.isErr()) {
        glDeleteShader(vert.value());
        return Result<ShaderProgram>::err(frag.error());
    }

    GLuint program = glCreateProgram();
    glAttachShader(program, vert.value());
    glAttachShader(program, frag.value());
    glLinkProgram(program);

    glDeleteShader(vert.value());
    glDeleteShader(frag.value());

    GLint linked = 0;
    glGetProgramiv(program, GL_LINK_STATUS, &linked);
    if (!linked) {
        char log[1024];
        glGetProgramInfoLog(program, sizeof(log), nullptr, log);
        glDeleteProgram(program);
        return Result<ShaderProgram>::err(
            std::string("Shader link error:\n") + log
        );
    }

    return Result<ShaderProgram>::ok(ShaderProgram(program));
}

Result<GLuint> ShaderProgram::compileStage(GLenum type, const std::string& src) {
    GLuint shader  = glCreateShader(type);
    const char* cs = src.c_str();
    glShaderSource(shader, 1, &cs, nullptr);
    glCompileShader(shader);

    GLint compiled = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
    if (!compiled) {
        char log[1024];
        glGetShaderInfoLog(shader, sizeof(log), nullptr, log);
        glDeleteShader(shader);
        return Result<GLuint>::err(
            std::string(type == GL_VERTEX_SHADER ? "Vertex" : "Fragment")
            + " shader compile error:\n" + log
        );
    }

    return Result<GLuint>::ok(shader);
}

GLint ShaderProgram::location(GLuint program, const char* name) {
    GLint loc = glGetUniformLocation(program, name);
    return loc;
}

void ShaderProgram::setInt  (const char* n, int v)           const { glUniform1i (location(m_id,n), v); }
void ShaderProgram::setFloat(const char* n, float v)         const { glUniform1f (location(m_id,n), v); }
void ShaderProgram::setBool (const char* n, bool v)          const { glUniform1i (location(m_id,n), v ? 1 : 0); }
void ShaderProgram::setVec2 (const char* n, const glm::vec2& v) const { glUniform2fv(location(m_id,n), 1, glm::value_ptr(v)); }
void ShaderProgram::setVec3 (const char* n, const glm::vec3& v) const { glUniform3fv(location(m_id,n), 1, glm::value_ptr(v)); }
void ShaderProgram::setVec4 (const char* n, const glm::vec4& v) const { glUniform4fv(location(m_id,n), 1, glm::value_ptr(v)); }
void ShaderProgram::setMat3 (const char* n, const glm::mat3& v) const { glUniformMatrix3fv(location(m_id,n), 1, GL_FALSE, glm::value_ptr(v)); }
void ShaderProgram::setMat4 (const char* n, const glm::mat4& v) const { glUniformMatrix4fv(location(m_id,n), 1, GL_FALSE, glm::value_ptr(v)); }

} 
