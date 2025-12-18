#include <renderer/Mesh.h>

//Mesh constructor - Binds VBO to VAO
Mesh::Mesh() {
    m_VAO.Bind();
    m_VBO.Bind();

    m_VAO.Link_VBO(m_VBO, 0, 3, GL_FLOAT, 0, 0);

    m_VAO.Unbind();
    m_VBO.Unbind();
}

//Initializes the VBO with it's first values and draw usage
void Mesh::Init_vertices(const std::vector<Vertex>& vertices, GLenum draw_usage) {
    m_vertex_count = vertices.size();
    m_VBO.Init_data(vertices, draw_usage);
}

//Updates all vertices(unless it is give less than it originaly has)
void Mesh::Update_vertices(const std::vector<Vertex>& vertices) {
    m_VBO.Update_data(vertices, vertices.size(), 0);
}

//Bind mesh for use
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
