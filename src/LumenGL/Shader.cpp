#include <LumenGL/Shader.h>
#include <iostream>

Shader::Shader() {}

//Create and compile a shader
Shader::Shader(const std::string& shaderFile, ShaderType type) {
    std::string content{};
    m_type = type;
   
    //Inform message for shader creation
    std::string msg = "SHADER: Trying to create shader from file: ";
    msg.append(shaderFile);
    Logger::Log(msg);

    //Try to get content of shader file
    try {
        content = GetFileContent(shaderFile);
    }
    catch(std::string msg) {
        Logger::Log(msg); 
        throw("SHADER: Unable to create a shader");
    }


    //Create shader based on type
    switch (m_type) {
        case ShaderType::VERTEX:
            m_ID = glCreateShader(GL_VERTEX_SHADER);
            break;
        case ShaderType::FRAGMENT:
            m_ID = glCreateShader(GL_FRAGMENT_SHADER);
            break;
        default:
            break;
    }

    const char* source = content.c_str();
    glShaderSource(m_ID, 1, &source, NULL);
    glCompileShader(m_ID);

    //Check for errors
    try {
        CompileErrors();
    }
    catch (std::string msg) {
        Logger::Log(msg); 
        throw ("SHADER: Unable to create a shader");
    }

    Logger::Log("SHADER: Shader created successfuly");
}

//Get content of shader file
std::string Shader::GetFileContent(const std::string& file) {
    std::ifstream in(file, std::ios::binary);
    if (in)
    {
        std::string contents;
        in.seekg(0, std::ios::end);
        contents.resize(in.tellg());
        in.seekg(0, std::ios::beg);
        in.read(&contents[0], contents.size());
        in.close();
        return(contents);
    }

    throw("SHADER: Can't opent the shader file");
}

//Check for errors in shader
void Shader::CompileErrors() {
    GLint hasCompiled;
    char infoLog[1024];
    glGetShaderiv(m_ID, GL_COMPILE_STATUS, &hasCompiled);
    if (hasCompiled == GL_FALSE)
    {
        glGetShaderInfoLog(m_ID, 1024, NULL, infoLog);
        std::string msg = "SHADER: Compiling failed, info: ";
        msg.append(infoLog);
        std::cout << msg << "\n";
        throw(msg);
    }
}

void Shader::Delete() {
    glDeleteShader(m_ID);
}

GLuint Shader::ShaderID() {
    return m_ID;
}
