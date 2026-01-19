#ifndef RENDERER_CLASS_H
#define RENDERER_CLASS_H

#include <glad/glad.h>

#include <glm/vec3.hpp>

#include <LumenGL/RenderObject.h>
#include <LumenGL/ShaderProgram.h>
#include <LumenGL/Camera.h>
#include <LumenGL/Scene.h>

namespace lumen::gl{
    class Renderer {
        public:
            //Constructors and ownership managment-----------

            Renderer();

            Renderer(const Renderer&) = delete;
            Renderer& operator=(const Renderer&) = delete;

            Renderer(Renderer&&) noexcept = delete;
            Renderer& operator=(Renderer&&) noexcept = delete;

            ~Renderer();

            //Getters and setters----------------------------

            void SetViewport(int x, int y, int width, int height);
            void SetColor(int r, int g, int b, int a);
            void SetActiveScene(Scene* scene);

            //Core interface---------------------------------

            void Init() const;
            void BeginFrame() const;
            void Render() const;
            void EndFrame() const;

        private:
            Scene* m_activeScene {nullptr};
            glm::vec4 m_clearColor {0.f, 0.f, 0.f, 1.f};
            glm::ivec4 m_viewport {0, 0, 800, 800};
    };

#endif

}
