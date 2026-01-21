#ifndef MATERIAL_CLASS_H
#define MATERIAL_CLASS_H

#include <memory>
#include <optional>

#include <glm/vec3.hpp>

#include <LumenGL/ShaderProgram.h>
#include <LumenGL/Texture.h>

class Material {
    public:
        //Constructors and ownership managment-----------

        Material();

        explicit Material(std::shared_ptr<ShaderProgram> program);

        Material(std::shared_ptr<ShaderProgram> program, const glm::vec3& baseColor, std::shared_ptr<Texture> texture = nullptr);

        Material(const Material&) = delete;
        Material& operator=(const Material&) = delete;

        Material(Material&&) noexcept = default;
        Material& operator=(Material&&) noexcept = default;

        ~Material() = default;

        //Getters and setters----------------------------

        void SetProgram(std::shared_ptr<ShaderProgram> program);
        [[nodiscard]] std::shared_ptr<ShaderProgram> GetProgram() const noexcept;

        void SetColor(const glm::vec3& color);
        [[nodiscard]] glm::vec3 GetColor() const noexcept;

        void SetTexture(std::shared_ptr<Texture> texture);
        [[nodiscard]] std::shared_ptr<Texture> GetTexture() const noexcept;

        //Core interface---------------------------------

        void Bind() const;
        void SetUniforms() const;
        void Unbind() const;
        void Delete() const;

    private:
        std::shared_ptr<ShaderProgram> m_program {nullptr};
        std::shared_ptr<Texture> m_texture = std::make_shared<Texture>();
        glm::vec3 m_color {1.f, 1.f, 1.f};
};

#endif
