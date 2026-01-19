#ifndef TRANSFORM_CLASS_H
#define TRANSFORM_CLASS_H

#include <memory>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define GLM_ENABLE_EXPERIMENTAL 
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

#include <LumenGL/ShaderProgram.h>

enum class Transformation {
    NONE,
    ROTATION,
    SCALING,
    TRANSLATION
};

class Transform {
    public:
        
        //Constructors and ownership managment-----------
        
        Transform();

        Transform(const Transform&) = delete;
        Transform& operator=(const Transform&) = delete;

        Transform(Transform&&) = default;
        Transform& operator=(Transform&&) = default;

        ~Transform();
        
        //Getters and setters----------------------------
        
        //Core interface---------------------------------
        
        void Rotate(float degrees, glm::vec3 direction);
        void Scale(float factor);
        void Translate(glm::vec3 shift);
        void Apply(std::shared_ptr<ShaderProgram> program, const char* uniform) const;
    
    private:
        glm::mat4 m_model = glm::mat4(1.0f);
        Transformation m_transformation = Transformation::NONE;
};

#endif
