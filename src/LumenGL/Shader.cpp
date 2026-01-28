#include <LumenGL/Shader.h>

#include <LumenGL/Logger.h>

Shader::Shader() {}

//Create and compile a shader
Shader::Shader(const std::string& shaderFile, ShaderType type) {
    std::string content{};
    m_type = type;

    content = GetFileContent(shaderFile);


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

    CompileErrors();
    
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

    LOG_ERROR("Failed to open the file: {}", file);
    return "";
}

//Check for errors in shader
void Shader::CompileErrors() {
    GLint hasCompiled;
    char infoLog[1024];
    glGetShaderiv(m_ID, GL_COMPILE_STATUS, &hasCompiled);
    if (hasCompiled == GL_FALSE)
    {
        glGetShaderInfoLog(m_ID, 1024, NULL, infoLog);
        LOG_ERROR("Failed to compile the shader file: {}", infoLog); 
    }

}

void Shader::Delete() {
    glDeleteShader(m_ID);
}

GLuint Shader::ShaderID() {
    return m_ID;
}
