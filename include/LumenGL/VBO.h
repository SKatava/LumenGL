#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include <glad/glad.h>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <vector>
#include <cstddef>

struct Vertex {
    glm::vec3 position;
    glm::vec2 texture_pos;
};


class VBO {
    public:
        //Constructors and ownership managment-----------
        
        VBO();

        VBO(const VBO&) = delete;
        VBO& operator=(const VBO&) = delete;

        VBO(VBO&&) noexcept = default;
        VBO& operator=(VBO&&) noexcept = default;

        ~VBO();
        
        //Getters and setters----------------------------
        
        //Core interface---------------------------------
        
        void Bind() const;
        void Unbind() const;
        void InitData(GLfloat* data, size_t size, GLenum drawUsage) const;
        void InitData(const std::vector<Vertex>& vertices, GLenum drawUsage) const;
        void UpdateData(GLfloat* data, size_t size, size_t offset) const;
        void UpdateData(const std::vector<Vertex>& vertices, size_t size, size_t offset) const;

    private:
        void create();
        void destroy();

        GLuint m_ID = 0;
};

#endif
