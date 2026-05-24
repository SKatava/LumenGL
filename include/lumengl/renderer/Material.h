// include/lumengl/renderer/Material.h
#pragma once
#include <memory>
#include <glm/vec4.hpp>
#include "lumengl/gpu/ShaderProgram.h"
#include "lumengl/gpu/Texture.h"

namespace lgl {

// Material does not own the shader — shaders are expensive and shared.
// Material owns its textures.
struct Material {
    const ShaderProgram* shader  {nullptr};   // non-owning, required
    const Texture*       albedo  {nullptr};   // non-owning, optional
    glm::vec4            color   {1.f, 1.f, 1.f, 1.f};

    // Bind shader + textures, set per-material uniforms
    void bind() const;
};

} // namespace lgl
