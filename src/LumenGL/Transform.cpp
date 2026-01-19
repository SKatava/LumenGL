#include <LumenGL/Transform.h>

Transform::Transform() {}

Transform::~Transform() {}

//Rotating the object with the model matrix
void Transform::Rotate(float degrees, glm::vec3 direction) {
    m_transformation = Transformation::ROTATION;
    m_model = glm::rotate(m_model, glm::radians(degrees), direction);
}

//Scaling the object with the model matrix
void Transform::Scale(float factor) {
    m_transformation = Transformation::SCALING;
    m_model = glm::scale(m_model, glm::vec3(factor, factor, factor));
}

void Transform::Translate(glm::vec3 shift) {
    m_transformation = Transformation::TRANSLATION;
    m_model = glm::translate(m_model, shift);
}

//Passing the model matrix to the desired shader 
void Transform::Apply(std::shared_ptr<ShaderProgram> program, const char* uniform) const {
    program->SetMat4(uniform, m_model);
}
