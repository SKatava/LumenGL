#include <LumenGL/EBO.h>

//Generates the EBO
EBO::EBO() { create(); }

EBO::~EBO() { destroy(); }

//Binds the EBO
void EBO::Bind() const{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);
}

//Unbinds the EBO
void EBO::Unbind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

//Sets the EBO's data
void EBO::SetIndices(GLuint* indices, size_t size, GLenum drawUsage) const {
    Bind();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size * sizeof(GLuint), indices, drawUsage);
    Unbind();
}

void EBO::SetIndices(const std::vector<GLuint>& indices, GLenum drawUsage) const {
    Bind();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), drawUsage);
    Unbind();
}

//Generates the EBO ID - private
void EBO::create() {
    glGenBuffers(1, &m_ID);
}

//Deletes the EBO - private
void EBO::destroy() {
    glDeleteBuffers(1, &m_ID);
}
