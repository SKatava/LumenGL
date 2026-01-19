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

        static std::unique_ptr<Material> CreateBasic(const glm::vec3& color = {1.0f, 1.0f, 1.0f});
        static std::unique_ptr<Material> CreateTextured(std::shared_ptr<Texture> texture, const glm::vec3& tint = {1.0f, 1.0f, 1.0f});

        //Getters and setters----------------------------

        void SetProgram(std::shared_ptr<ShaderProgram> program);
        [[nodiscard]] std::shared_ptr<ShaderProgram> GetProgram() const noexcept;

        void SetColor(const glm::vec3& color);
        [[nodiscard]] glm::vec3 GetColor() const noexcept;

        void SetTexture(std::shared_ptr<Texture> texture);
        [[nodiscard]] std::shared_ptr<Texture> GetTexture() const noexcept;

        //Core interface---------------------------------

        void Bind() const;
        void Unbind() const;
        void Delete() const;

    private:
        std::shared_ptr<ShaderProgram> m_program;
        std::shared_ptr<Texture> m_texture;
        glm::vec3 m_color;
};

#endif
