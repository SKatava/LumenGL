// src/renderer/Renderer.cpp
#include "lumengl/renderer/Renderer.h"
#include <glad/glad.h>
#include <algorithm>
#include <cassert>

namespace lgl {

void Renderer::setClearColor(float r, float g, float b, float a) {
    m_clearColor = {r, g, b, a};
}

void Renderer::setWireframe(bool enabled) {
    glPolygonMode(GL_FRONT_AND_BACK, enabled ? GL_LINE : GL_FILL);
}

void Renderer::beginFrame() const {
    glClearColor(m_clearColor.r, m_clearColor.g,
                 m_clearColor.b, m_clearColor.a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::submit(const DrawCall& call) {
    assert(call.mesh     && "DrawCall has no mesh");
    assert(call.material && "DrawCall has no material");
    m_queue.push_back({ call.mesh, call.material, call.transform });
}

void Renderer::flush(const Camera& camera) {
    // Sort by shader ID to minimize state changes
    std::stable_sort(m_queue.begin(), m_queue.end(),
        [](const RenderItem& a, const RenderItem& b) {
            return a.material->shader->id() < b.material->shader->id();
        }
    );

    for (const RenderItem& item : m_queue)
        drawItem(item, camera);

    m_queue.clear();
}

void Renderer::endFrame() {
    m_queue.clear(); // safety — clear even if flush wasn't called
}

void Renderer::drawItem(const RenderItem& item, const Camera& cam) const {
    item.material->bind();

    const ShaderProgram* shader = item.material->shader;
    shader->setMat4("u_model",      item.transform);
    shader->setMat4("u_view",       cam.view());
    shader->setMat4("u_projection", cam.projection());
    shader->setVec3("u_camPos",     cam.position());

    item.mesh->bind();
    glDrawElements(GL_TRIANGLES, item.mesh->indexCount(), GL_UNSIGNED_INT, nullptr);
    item.mesh->unbind();
}

} // namespace lgl
