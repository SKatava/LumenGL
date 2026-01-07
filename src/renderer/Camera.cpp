#include <renderer/Camera.h>

Camera::Camera() {}

Camera::Camera(int width, int height, glm::vec3 position) {
    m_width = width;
    m_height = height;
    m_position = position;
}   

void Camera::Matrix(float FOVdeg, float nearPlane, float farPlane, Shader_program& program, const char* uniform) {
    	// Initializes matrices since otherwise they will be the null matrix
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);

	// Makes camera look in the right direction from the right position
	view = glm::lookAt(m_position, m_position + m_orientation, m_up);
	// Adds perspective to the scene
	projection = glm::perspective(glm::radians(FOVdeg), (float)m_width / m_height, nearPlane, farPlane);

	// Exports the camera matrix to the Vertex Shader
	glUniformMatrix4fv(glGetUniformLocation(program.Get_ID(), uniform), 1, GL_FALSE, glm::value_ptr(projection * view));    
}

