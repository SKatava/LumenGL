// include/lumengl/gpu/Texture.h
#pragma once
#include <glad/glad.h>
#include <string>
#include "lumengl/util/Result.h"

namespace lgl {

struct TextureConfig {
    GLenum wrapS     {GL_REPEAT};
    GLenum wrapT     {GL_REPEAT};
    GLenum minFilter {GL_LINEAR_MIPMAP_LINEAR};
    GLenum magFilter {GL_LINEAR};
    bool   flipY     {true};
};

class Texture {
public:
    [[nodiscard]]
    static Result<Texture> fromFile(const std::string& path,
                                    TextureConfig config = {});

    [[nodiscard]]
    static Texture createWhite();   // 1x1 white — safe default

    ~Texture() { if (m_id) glDeleteTextures(1, &m_id); }

    Texture(const Texture&)            = delete;
    Texture& operator=(const Texture&) = delete;

    Texture(Texture&& o) noexcept : m_id(o.m_id) { o.m_id = 0; }
    Texture& operator=(Texture&& o) noexcept {
        if (this != &o) {
            if (m_id) glDeleteTextures(1, &m_id);
            m_id = o.m_id;
            o.m_id = 0;
        }
        return *this;
    }

    // Bind to a texture unit
    void bind(GLuint unit = 0) const {
        glActiveTexture(GL_TEXTURE0 + unit);
        glBindTexture(GL_TEXTURE_2D, m_id);
    }

    [[nodiscard]] GLuint id()     const noexcept { return m_id; }
    [[nodiscard]] int    width()  const noexcept { return m_width; }
    [[nodiscard]] int    height() const noexcept { return m_height; }

private:
    Texture(GLuint id, int w, int h) : m_id(id), m_width(w), m_height(h) {}

    GLuint m_id     {0};
    int    m_width  {0};
    int    m_height {0};
};

} // namespace lgl
