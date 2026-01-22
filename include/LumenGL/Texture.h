#ifndef TEXTURE_CLASS_H
#define TEXTURE_CLASS_H

#include <memory>

#include <glad/glad.h>
#include <stb/stb_image.h>

#include <LumenGL/ShaderProgram.h>

class Texture {
    public:
        //Constructors and ownership managment-----------
        
        Texture();
        
        explicit Texture(const char* image, GLenum texture_type, GLenum slot, GLenum format, GLenum pixel_type);

        Texture(const Texture&) = delete;
        Texture& operator=(const Texture&) = delete;

        Texture(Texture&&) noexcept = default;
        Texture& operator=(Texture&&) noexcept = default;

        ~Texture();

        //Getters and setters----------------------------


        //Core interface---------------------------------

        void TextureUnit(std::shared_ptr<ShaderProgram> program, const char* uniform, GLuint unit) const;
        void Bind() const;
        void Unbind() const;

    private:
        void destroy() const;
        void createDefault(); 

        GLuint m_ID;
        GLenum m_type = GL_TEXTURE_2D;
};

#endif
