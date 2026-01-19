#ifndef VAO_CLASS_H
#define VAO_CLASS_H

#include <glad/glad.h>
#include <cstddef>

#include <LumenGL/VBO.h>

class VAO {
    public:
        //Constructors and ownership managment-----------
        
        VAO();
        
        VAO(const VAO&) = delete;
        VAO& operator=(const VAO&) = delete;

        VAO(VAO&&) noexcept = default;
        VAO& operator=(VAO&&) noexcept = default;
        
        ~VAO();

        //Getters and setters----------------------------

        //Core interface---------------------------------

        void Bind() const;
        void Unbind() const;
        void LinkVBO(const VBO& VBO, GLuint layout, GLint size, GLenum type, size_t space, size_t offset) const;

    private:
        void create();
        void destroy() noexcept;

        GLuint m_ID = 0;

};

#endif
