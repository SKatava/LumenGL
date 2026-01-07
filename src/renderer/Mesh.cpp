#include <renderer/Mesh.h>

//Mesh constructor - Binds VBO to VAO
Mesh::Mesh() {
    m_VAO.Bind();
    m_VBO.Bind();

    m_VAO.Link_VBO(m_VBO, 0, 3, GL_FLOAT, 5, 0);
    m_VAO.Link_VBO(m_VBO, 1, 2, GL_FLOAT, 5, 3);

    m_VAO.Unbind();
    m_VBO.Unbind();
}

//Initializes the VBO with it's first values and draw usage
void Mesh::Init_vertices(const std::vector<Vertex>& vertices, GLenum draw_usage) {
    m_vertex_count = vertices.size();
    m_VBO.Init_data(vertices, draw_usage);
}

//Set the indices(order in which vertices are used)
void Mesh::Init_indices(GLuint* indices, size_t size ,GLenum draw_usage) {
     m_EBO.Set_indices(indices, size, draw_usage);
}

//Updates all vertices(unless it is given less than it originaly has)
void Mesh::Update_vertices(const std::vector<Vertex>& vertices) {
    m_VBO.Update_data(vertices, vertices.size(), 0);
}

//Bind mesh for usage
void Mesh::Bind() const {
    m_VAO.Bind();
}

//Get number of vertices
const unsigned& Mesh::Get_vertices_count() {
    return m_vertex_count;
}

//Deletes the data(VBO, VAO)
void Mesh::Delete() {
    m_VAO.Delete();
    m_VBO.Delete();
}
