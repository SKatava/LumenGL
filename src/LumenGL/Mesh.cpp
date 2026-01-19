#include <LumenGL/Mesh.h>

//Mesh constructor - Binds VBO to VAO
Mesh::Mesh() {
    m_VAO.Bind();
    m_EBO.Bind();
    m_VBO.Bind();

    m_VAO.LinkVBO(m_VBO, 0, 3, GL_FLOAT, 5, 0);
    m_VAO.LinkVBO(m_VBO, 1, 2, GL_FLOAT, 5, 3);

    m_VAO.Unbind();
    m_EBO.Unbind();
    m_VBO.Unbind();
}

//Initializes the VBO with it's first values and draw usage
void Mesh::InitVertices(const std::vector<Vertex>& vertices, GLenum drawUsage) {
    m_vertexCount = vertices.size();
    m_VBO.InitData(vertices, drawUsage);
}

//Set the indices(order in which vertices are used)
void Mesh::InitIndices(const std::vector<GLuint>& indices, GLenum drawUsage) {
     m_EBO.SetIndices(indices, drawUsage);
     m_indicesCount = indices.size();
}

//Updates all vertices(unless it is given less than it originaly has)
void Mesh::UpdateVertices(const std::vector<Vertex>& vertices) {
    m_VBO.UpdateData(vertices, vertices.size(), 0);
}

//Bind mesh for usage
void Mesh::Bind() const {
    m_VAO.Bind();
}

//Get number of vertices
const unsigned& Mesh::GetVerticesCount() {
    return m_vertexCount;
}

//Get number of vertices
const unsigned& Mesh::GetIndicesCount() {
    return m_indicesCount;
}


