#ifndef TRANSFORM_CLASS_H
#define TRANSFORM_CLASS_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define GLM_ENABLE_EXPERIMENTAL 
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

#include <renderer/Shader_program.h>

enum class Transformation {
    NONE,
    ROTATION,
    SCALING,
    TRANSLATION
};

class Transform {
    public:
        Transform();
        void Rotate(float degrees, glm::vec3 direction);
        void Scale(float factor);
        void Translate(glm::vec3 shift);
        void Apply(Shader_program& program, const char* uniform);
    private:
        glm::mat4 m_model = glm::mat4(1.0f);
        Transformation m_transformation = Transformation::NONE;
};

#endif
