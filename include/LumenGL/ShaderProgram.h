#ifndef SHADERPROGRAM_CLASS_H
#define SHADERPROGRAM_CLASS_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

#include <LumenGL/Shader.h>
#include <LumenGL/Logger.h>


class ShaderProgram {
    public:
        //Constructors and ownership managment-----------
        
        ShaderProgram();
        
        explicit ShaderProgram(const std::vector<std::string>& files, const std::vector<ShaderType>& types);
        
        ShaderProgram(const ShaderProgram&) = delete;      
        ShaderProgram& operator=(const ShaderProgram&) = delete;

        ShaderProgram(ShaderProgram&&) noexcept = default;
        ShaderProgram& operator=(ShaderProgram&&) noexcept = default;

        ~ShaderProgram() = default;

        //Getters and setters----------------------------

        const GLuint& GetID() const;
       
        //Core interface---------------------------------

        void Activate() const;
        void Deactivate() const;
        void Delete() const;
        void CompileErrors() const;
        void SetVec3(const std::string& name, const glm::vec3& value) const;
        void SetMat4(const std::string& name, const glm::mat4& value) const;

    private:
        GLuint m_ID;
};

#endif
