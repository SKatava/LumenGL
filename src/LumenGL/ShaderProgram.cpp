#include <LumenGL/ShaderProgram.h>

//Default constructor
ShaderProgram::ShaderProgram() {}

//Construct an actual shader program with given files and shader types, the file and type should share same index in vector
ShaderProgram::ShaderProgram(const std::vector<std::string>& files, const std::vector<ShaderType>& types) {
    m_ID = glCreateProgram();
    
    for(size_t i{}; i < files.size(); ++i) {
        Shader shader;

        try {
            shader = Shader(files[i], types[i]); 
        }
        catch(std::string msg) {
            Logger::Log(msg); 
            throw("SHADER_PROGRAM: Can't create the shader program");
        }


        glAttachShader(m_ID, shader.ShaderID());
        shader.Delete();
    }

    glLinkProgram(m_ID);
    Logger::Log("SHADER_PROGRAM: Shader program created successfuly");
}

//Get the shader program(ID)
const GLuint& ShaderProgram::GetID() const {
    return m_ID;
}

//Activates the program
void ShaderProgram::Activate() const {
    glUseProgram(m_ID);
}

//Deactivates the program
void ShaderProgram::Deactivate() const {
    glUseProgram(0);
}

void ShaderProgram::SetVec3(const std::string& name, const glm::vec3& value) const {
    GLint loc = glGetUniformLocation(m_ID, name.c_str());
    glUniform3f(loc, value.r, value.g, value.b);
}

void ShaderProgram::SetMat4(const std::string& name, const glm::mat4& value) const {
    GLint loc = glGetUniformLocation(m_ID, name.c_str());
    glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(value));  
}

//Deletes the program
void ShaderProgram::Delete() const {
    glDeleteProgram(m_ID);
}

//Checks for errors when linking shaders
void ShaderProgram::CompileErrors() const {
    GLint hasCompiled;
    char infoLog[1024];
    glGetProgramiv(m_ID, GL_LINK_STATUS, &hasCompiled);
    if (hasCompiled == GL_FALSE)
    {
        glGetProgramInfoLog(m_ID, 1024, NULL, infoLog);
        std::string msg = "SHADER_PROGRAM: Compiling failed, info: ";
        msg.append(infoLog);
        throw(msg);
    }
}


