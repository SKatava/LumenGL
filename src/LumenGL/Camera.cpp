#include <LumenGL/Camera.h>

//Default constructor
Camera::Camera() {}

//Constructor for initializing default values
Camera::Camera(int width, int height, glm::vec3 position) {
    m_width = width;
    m_height = height;
    m_position = position;
}   

//Calculating and passing the matrix to the deisred shader
void Camera::UpdateMatrix(float FOVdeg, float nearPlane, float farPlane) {
    glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);

	view = glm::lookAt(m_position, m_position + m_orientation, m_up);
	projection = glm::perspective(glm::radians(FOVdeg), (float)m_width / m_height, nearPlane, farPlane);

    m_matrix = projection * view;

}

void Camera::UploadMatrix(std::shared_ptr<ShaderProgram> program, const char* uniform) const {
    program->SetMat4(uniform, m_matrix);
}



