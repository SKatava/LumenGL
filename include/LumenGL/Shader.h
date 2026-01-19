#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include <glad/glad.h>
#include <string>
#include <fstream>

#include <LumenGL/Logger.h>

enum class ShaderType {
    VERTEX,
    FRAGMENT,
};

class Shader {
    public:
        Shader();
        Shader(const std::string& shaderFile, ShaderType type);
        std::string GetFileContent(const std::string& file);
        void CompileErrors();
        GLuint ShaderID();
        void Delete();
    private:
        GLuint m_ID;
        ShaderType m_type;
};

#endif
