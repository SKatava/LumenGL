#ifndef MESH_CLASS_H
#define MESH_CLASS_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>

#include <LumenGL/VAO.h>
#include <LumenGL/EBO.h>
#include <LumenGL/ShaderProgram.h>

class Mesh {
    public:

        //Constructors and ownership managment-----------
        
        Mesh();

        Mesh(const Mesh&) = delete;
        Mesh& operator=(const Mesh&) = delete;

        Mesh(Mesh&&) noexcept = default;
        Mesh& operator=(Mesh&&) noexcept = default;

        ~Mesh() = default;
        
        //Getters and setters----------------------------
        
        [[nodiscard]] const unsigned& GetVerticesCount();
        [[nodiscard]] const unsigned& GetIndicesCount();
        
        //Core interface---------------------------------
        
        void InitVertices(const std::vector<Vertex>& vertices, GLenum drawUsage = GL_STATIC_DRAW);
        void InitIndices(const std::vector<GLuint>& indices, GLenum drawUsage = GL_STATIC_DRAW);
        void UpdateVertices(const std::vector<Vertex>& vertices);
        void Bind() const;
    
    private:
        VAO m_VAO;
        VBO m_VBO;
        EBO m_EBO;
        unsigned m_vertexCount = 0;
        unsigned m_indicesCount = 0;
};

#endif
