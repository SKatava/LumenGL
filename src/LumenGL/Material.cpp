#include <LumenGL/Material.h>

Material::Material() {}

Material::Material(std::shared_ptr<ShaderProgram> program)
    : m_program(std::move(program))
{}

Material::Material(std::shared_ptr<ShaderProgram> program, const glm::vec3& baseColor, std::shared_ptr<Texture> texture)
    : m_program(std::move(program)), m_texture(std::move(texture)), m_color(baseColor)
{}

void Material::Bind() const {
    if (!m_program) return;
    m_program->Activate();
    if(!m_texture) return;
    m_texture->Bind();
}

void Material::SetUniforms() const {
    m_program->SetVec3("u_color", m_color);
    if(!m_texture) return;
    m_texture->TextureUnit(m_program, "tex0", 0);
}

void Material::Unbind() const {
    if(!m_texture) return;
    m_texture->Unbind();
}

void Material::SetProgram(std::shared_ptr<ShaderProgram> program) {
    m_program = std::move(program);
}

std::shared_ptr<ShaderProgram> Material::GetProgram() const noexcept {
    return m_program;
}

void Material::SetColor(const glm::vec3& color) {
    m_color = color;
}

glm::vec3 Material::GetColor() const noexcept {
    return m_color;
}

void Material::SetTexture(std::shared_ptr<Texture> texture) {
    m_texture = std::move(texture);
}

std::shared_ptr<Texture> Material::GetTexture() const noexcept {
    return m_texture;
}

/*void Material::TrySetUniforms() const
{
    if (!m_shader) return;

    m_shader->SetVec3("uBaseColor", m_baseColor);

    if (m_albedoTexture)
    {
        m_albedoTexture->Bind(0);
        m_shader->SetInt("uAlbedoMap", 0);
    }
}
*/
