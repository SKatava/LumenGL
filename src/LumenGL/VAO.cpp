#include <LumenGL/VAO.h>

//Generates the VAO
VAO::VAO() { create(); }

//Destroy the VAO
VAO::~VAO() { destroy(); }

//Binds the VAO
void VAO::Bind() const {
    glBindVertexArray(m_ID);
}

//Unbinds the VAO
void VAO::Unbind() const {
    glBindVertexArray(0);
}

//Link the VBO to the VAO
void VAO::LinkVBO(const VBO &VBO, GLuint layout, GLint size, GLenum type, size_t space, size_t offset) const {
    VBO.Bind();
    glVertexAttribPointer(layout, size, type, GL_FALSE, space * sizeof(GLfloat), (void*)( offset * sizeof(GLfloat)) );
    glEnableVertexAttribArray(layout);
    VBO.Unbind();
}

//Generate the VAO ID - private
void VAO::create() {
    glGenVertexArrays(1, &m_ID);
}

//Delete the VAO ID - private
void VAO::destroy() noexcept{
   glDeleteVertexArrays(1, &m_ID); 
}

