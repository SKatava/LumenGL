// src/renderer/Material.cpp
#include "lumengl/renderer/Material.h"
#include <cassert>

namespace lgl {

void Material::bind() const {
    assert(shader && "Material has no shader");
    shader->use();
    shader->setVec4("u_color", color);

    if (albedo) {
        albedo->bind(0);
        shader->setInt("u_albedo",    0);
        shader->setBool("u_hasAlbedo", true);
    } else {
        shader->setBool("u_hasAlbedo", false);
    }
}

} // namespace lgl
