// include/lumengl/renderer/Renderer.h
#pragma once
#include <glad/glad.h>
#include <glm/vec4.hpp>
#include "Mesh.h"
#include "Material.h"
#include "Camera.h"

namespace lgl {

struct DrawCall {
    const Mesh*     mesh     {nullptr};
    const Material* material {nullptr};
    glm::mat4       transform{1.f};
};

class Renderer {
public:
    Renderer() = default;

    // Non-copyable
    Renderer(const Renderer&)            = delete;
    Renderer& operator=(const Renderer&) = delete;

    // State
    void setClearColor(float r, float g, float b, float a = 1.f);
    void setWireframe(bool enabled);

    // Per-frame API — explicit, no hidden state
    void beginFrame() const;
    void submit(const DrawCall& call);  // batches, doesn't draw yet
    void flush(const Camera& camera);   // sorts and draws all submitted calls
    void endFrame();              // just clears the queue

private:
    glm::vec4 m_clearColor {0.05f, 0.05f, 0.05f, 1.f};

    struct RenderItem {
        const Mesh*     mesh;
        const Material* material;
        glm::mat4       transform;
    };
    std::vector<RenderItem> m_queue;

    void drawItem(const RenderItem& item, const Camera& cam) const;
};

} // namespace lgl
