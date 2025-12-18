#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include <glad/glad.h>
#include <glm/vec3.hpp>
#include <vector>
#include <cstddef>

struct Vertex {
    glm::vec3 position;
    //glm::vec3 color;
};


class VBO {
    public:
        VBO();
        void Bind();
        void Init_data(GLfloat* data, size_t size, GLenum draw_usage);
        void Init_data(const std::vector<Vertex>& vertices, GLenum draw_usage);
        void Update_data(GLfloat* data, size_t size, size_t offset);
        void Update_data(const std::vector<Vertex>& vertices, size_t size, size_t offset);
        void Unbind();
        void Delete();
    private:
        GLuint m_ID;
};

#endif
