#ifndef RENDEROBJECTBUILDER_CLASS_H
#define RENDEROBJECTBUILDER_CLASS_H

#include <vector>
#include <string>
#include <glm/glm.hpp>
#include <memory>

#include <LumenGL/Mesh.h>
#include <LumenGL/Material.h>
#include <LumenGL/RenderObject.h>
#include <LumenGL/ShaderProgram.h>

namespace lumen::gl {
    class RenderObjectBuilder {
        public:
            explicit RenderObjectBuilder(std::string name = "UNAMED");

            RenderObjectBuilder& WithVertices(const std::vector<Vertex>& vertices);
            RenderObjectBuilder& WithIndices(const std::vector<GLuint>& indices);
            RenderObjectBuilder& WithPrimitive(GLenum mode = GL_TRIANGLES);

            RenderObjectBuilder& WithProgram(std::shared_ptr<ShaderProgram> program);
            RenderObjectBuilder& WithColor(const glm::vec3& color);
            RenderObjectBuilder& WithTexture(std::shared_ptr<Texture> textureh);

            std::shared_ptr<RenderObject> Build();

            static RenderObjectBuilder Create(std::string name= "UNAMED");

        private:
            RenderObject m_obj;
            std::string m_name;
    };
}

#endif
