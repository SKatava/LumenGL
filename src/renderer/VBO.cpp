#include <renderer/VBO.h>


//Generate the VBOvbo
VBO::VBO() {
    glGenBuffers(1, &m_ID);
}

//Binds the VBO
void VBO::Bind() {
    glBindBuffer(GL_ARRAY_BUFFER, m_ID);
}

//Unbinds the VBO
void VBO::Unbind() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

//Initialize first data into the buffer- custom data
void VBO::Init_data(GLfloat* data, size_t size, GLenum draw_usage) {
    Bind();
    glBufferData(GL_ARRAY_BUFFER, size * sizeof(GLfloat), data, draw_usage);
    Unbind();
}

//Initialize first data into the buffer - Vertex data
void VBO::Init_data(const std::vector<Vertex>& vertices, GLenum draw_usage) {
    Bind();
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), draw_usage);
    Unbind();
}

//Update data of the buffer(no memory allocations) - custom data
void VBO::Update_data(GLfloat* data, size_t size, size_t offset) {
    Bind();
    glBufferSubData(GL_ARRAY_BUFFER, offset * sizeof(GLfloat), size * sizeof(GLfloat), data);
    Unbind();
}

//Update data of the buffer(no memory allocations) - Vertex data
void VBO::Update_data(const std::vector<Vertex>& vertices, size_t size, size_t offset) {
    Bind();
    glBufferSubData(GL_ARRAY_BUFFER, offset * sizeof(Vertex), size * sizeof(Vertex), vertices.data());
    Unbind();
}

//Deletes the VBO
void VBO::Delete() {
    glDeleteBuffers(1, &m_ID);
}

