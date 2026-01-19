#ifndef RENDEROBJECT_STRUCT_H
#define RENDEROBJECT_STRUCT_H

#include <memory>

#include <LumenGL/Mesh.h>
#include <LumenGL/Material.h>
#include <LumenGL/Transform.h>

namespace lumen::gl {
    struct RenderObject {
        //Members----------------------------------------

        std::shared_ptr<Mesh> mesh {nullptr};
        std::shared_ptr<Material> material {nullptr};
        Transform transform {};
        GLenum drawMode {GL_TRIANGLES};

        //Constructors and ownership managment-----------

        RenderObject() = default;

        RenderObject(const RenderObject&) = delete;
        RenderObject& operator=(const RenderObject&) = delete;

        RenderObject(RenderObject&&) noexcept = default;
        RenderObject& operator=(RenderObject&&) noexcept = default;
    };
}

#endif
