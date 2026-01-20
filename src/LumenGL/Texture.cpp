#include <LumenGL/Texture.h>

//Contructor - create a default texture
Texture::Texture() {
    const int SIZE = 8;
    glm::uint32 pixels[SIZE*SIZE];
    glm::uint32 colorA = 0xFFFFFFFF;
    glm::uint32 colorB = 0xFF404040;

    for(int y{}; y < SIZE; ++y) {
        for(int x{}; x < SIZE; ++x) {
            bool even = ( (x + y) % 2 ) == 0;
            pixels[y * SIZE + x] = even ? colorA : colorB;
        }
    }

    glGenTextures(1, &m_ID);

    glActiveTexture(GL_TEXTURE0);

    glBindTexture(m_type, m_ID);

    glTextureParameteri(m_type, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
    glTextureParameteri(m_type, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexParameteri(m_type, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(m_type, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexImage2D(m_type, 0, GL_RGBA8, SIZE, SIZE, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

    glGenerateMipmap(m_type);

    glBindTexture(m_type, 0);
}

//Destroy the texture
Texture::~Texture() { destroy(); }

//Generate the texture and set the default parameters
Texture::Texture(const char* image, GLenum texture_type, GLenum slot, GLenum format, GLenum pixel_type) {
    m_type = texture_type;

    int width, height, num_col_ch;

    stbi_set_flip_vertically_on_load(true);

    unsigned char* bytes = stbi_load(image, &width, &height, &num_col_ch, 0);

    glGenTextures(1, &m_ID);

    glActiveTexture(slot);

    glBindTexture(m_type, m_ID);

    glTextureParameteri(m_type, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
    glTextureParameteri(m_type, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexParameteri(m_type, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(m_type, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexImage2D(m_type, 0, GL_RGB, width, height, 0, format, pixel_type, bytes);

    glGenerateMipmap(m_type);

    stbi_image_free(bytes);

    glBindTexture(m_type, 0);
}

//Pass the texture to the shader program(as uniform)
void Texture::TextureUnit(std::shared_ptr<ShaderProgram> program, const char* uniform, GLuint unit) const {
	GLuint texture_uniform = glGetUniformLocation(program->GetID(), uniform);
    program->Activate();
	glUniform1i(texture_uniform, unit); 
}

//Bind the texture
void Texture::Bind() const {
    glBindTexture(m_type, m_ID);
}

//Unbind the texture
void Texture::Unbind() const {
    glBindTexture(m_type, 0);
}

//Delete the texture
void Texture::destroy() {
    glDeleteTextures(1, &m_ID);
}
