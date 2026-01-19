// RenderObjectBuilder.cpp
#include <LumenGL/RenderObjectBuilder.h>

namespace lumen::gl {

    RenderObjectBuilder::RenderObjectBuilder(std::string name){
        m_obj.mesh     = std::make_shared<Mesh>();
        m_obj.material = std::make_shared<Material>();
        m_obj.drawMode = GL_TRIANGLES;
        m_name         = name;
    }

    RenderObjectBuilder& RenderObjectBuilder::WithVertices(const std::vector<Vertex>& vertices) {
        m_obj.mesh->InitVertices(vertices, GL_STATIC_DRAW);
        return *this;
    }

    RenderObjectBuilder& RenderObjectBuilder::WithIndices(const std::vector<GLuint>& indices) {
        m_obj.mesh->InitIndices(indices, GL_STATIC_DRAW);
        return *this;
    }

    RenderObjectBuilder& RenderObjectBuilder::WithPrimitive(GLenum mode) {
        m_obj.drawMode = mode;
        return *this;
    }

    RenderObjectBuilder& RenderObjectBuilder::WithProgram(std::shared_ptr<ShaderProgram> program) {
        m_obj.material->SetProgram(program);
        return *this;
    }

    RenderObjectBuilder& RenderObjectBuilder::WithColor(const glm::vec3& color) {
        m_obj.material->SetColor(color);
        return *this;
    }

    RenderObjectBuilder& RenderObjectBuilder::WithTexture(std::shared_ptr<Texture> texture) {
        m_obj.material->SetTexture(texture);
        return *this;
    }


    std::shared_ptr<RenderObject> RenderObjectBuilder::Build() {
        auto ptr = std::make_shared<RenderObject>(std::move(m_obj));
        return ptr;
    }

    RenderObjectBuilder RenderObjectBuilder::Create(std::string name) {
        return RenderObjectBuilder(std::move(name));
    }

} 
