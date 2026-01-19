#include <LumenGL/VBO.h>


//Generate the VBO
VBO::VBO() { create(); }

//Destroy the VBO
VBO::~VBO() { destroy(); }

//Binds the VBO
void VBO::Bind() const {
    glBindBuffer(GL_ARRAY_BUFFER, m_ID);
}

//Unbinds the VBO
void VBO::Unbind() const {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

//Initialize first data into the buffer- custom data
void VBO::InitData(GLfloat* data, size_t size, GLenum drawUsage) const {
    Bind();
    glBufferData(GL_ARRAY_BUFFER, size * sizeof(GLfloat), data, drawUsage);
    Unbind();
}

//Initialize first data into the buffer - Vertex data
void VBO::InitData(const std::vector<Vertex>& vertices, GLenum drawUsage) const {
    Bind();
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), drawUsage);
    Unbind();
}

//Update data of the buffer(no memory allocations) - custom data
void VBO::UpdateData(GLfloat* data, size_t size, size_t offset) const {
    Bind();
    glBufferSubData(GL_ARRAY_BUFFER, offset * sizeof(GLfloat), size * sizeof(GLfloat), data);
    Unbind();
}

//Update data of the buffer(no memory allocations) - Vertex data
void VBO::UpdateData(const std::vector<Vertex>& vertices, size_t size, size_t offset) const {
    Bind();
    glBufferSubData(GL_ARRAY_BUFFER, offset * sizeof(Vertex), size * sizeof(Vertex), vertices.data());
    Unbind();
}

void VBO::create() {
    glGenBuffers(1, &m_ID);
}

//Deletes the VBO
void VBO::destroy() {
    glDeleteBuffers(1, &m_ID);
}

