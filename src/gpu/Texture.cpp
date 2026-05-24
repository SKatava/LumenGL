#include "lumengl/gpu/Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

namespace lgl {

Texture Texture::createWhite() {
    GLuint id;
    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);

    // 1x1 white RGBA pixel
    const uint8_t white[4] = { 255, 255, 255, 255 };
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0,
                 GL_RGBA, GL_UNSIGNED_BYTE, white);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    return Texture(id, 1, 1);
}

Result<Texture> Texture::fromFile(const std::string& path, TextureConfig config) {
    stbi_set_flip_vertically_on_load(config.flipY);

    int w, h, channels;
    uint8_t* data = stbi_load(path.c_str(), &w, &h, &channels, 0);

    if (!data)
        return Result<Texture>::err("Failed to load texture: " + path);

    GLenum internalFmt = GL_RGB;
    GLenum fmt         = GL_RGB;
    if (channels == 4) { internalFmt = GL_RGBA; fmt = GL_RGBA; }
    if (channels == 1) { internalFmt = GL_RED;  fmt = GL_RED;  }

    GLuint id;
    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);

    glTexImage2D(GL_TEXTURE_2D, 0, internalFmt, w, h, 0,
                 fmt, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,     config.wrapS);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,     config.wrapT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, config.minFilter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, config.magFilter);

    stbi_image_free(data);
    return Result<Texture>::ok(Texture(id, w, h));
}

} // namespace lgl
