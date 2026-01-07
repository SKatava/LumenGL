#ifndef MESH_CLASS_H
#define MESH_CLASS_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>

#include <renderer/VAO.h>
#include <renderer/EBO.h>
#include <renderer/Shader_program.h>

class Mesh {
    public:
        Mesh();
        void Init_vertices(const std::vector<Vertex>& vertices, GLenum draw_usage);
        void Init_indices(GLuint* indices, size_t size, GLenum draw_usage);
        void Update_vertices(const std::vector<Vertex>& vertices);
        void Bind() const;
        const unsigned& Get_vertices_count();
        void Delete();
    private:
        VAO m_VAO;
        VBO m_VBO;
        EBO m_EBO;
        unsigned m_vertex_count = 0;
};

#endif
