#ifndef RENDERER_CLASS_H
#define RENDERER_CLASS_H

#include <glad/glad.h>
#include <vector>

#include <renderer/Render_object.h>
#include <renderer/Shader_program.h>
#include <renderer/Camera.h>

class Renderer {
    public:
        Renderer();
        void Init();
        void Render();
        void Shutdown();
    private:
        Shader_program m_program;
        Render_object obj;
        Camera cam;
};

#endif
