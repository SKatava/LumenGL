#ifndef CAMERA_CLASS_H
#define CAMERA_CLASS_H

#include <memory>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define GLM_ENABLE_EXPERIMENTAL 
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

#include <LumenGL/ShaderProgram.h>

class Camera {
    public:
        Camera();
        Camera(int width, int heigth, glm::vec3 position);
        void Update_matrix();
        void Matrix(float FOVdeg, float nearPlane, float farPlane, std::shared_ptr<ShaderProgram> program, const char* uniform);

    private:
        glm::vec3 m_position;
        glm::vec3 m_orientation = glm::vec3(0.f, 0.f, -1.f);
        glm::vec3 m_up = glm::vec3(0.f, 1.f, 0.f);
        glm::mat4 m_matrix = glm::mat4(1.f);
        
        int m_width;
        int m_height;

        float m_speed = 0.1f;
        float m_sensitivity = 100.f;
};

#endif
