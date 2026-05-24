// src/Context.cpp
#include "lumengl/Context.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdexcept>

namespace lgl {

Result<Context> Context::create(ContextConfig config) {
    if (!glfwInit())
        return Result<Context>::err("Failed to initialize GLFW");

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, config.glMajor);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, config.glMinor);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, config.msaaSamples);

    GLFWwindow* window = glfwCreateWindow(
        config.width, config.height, config.title.c_str(), nullptr, nullptr
    );

    if (!window) {
        glfwTerminate();
        return Result<Context>::err("Failed to create GLFW window");
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(config.vsync ? 1 : 0);

    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
        glfwDestroyWindow(window);
        glfwTerminate();
        return Result<Context>::err("Failed to initialize GLAD");
    }

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_MULTISAMPLE);

    return Result<Context>::ok(Context(window, config));
}

Context::Context(GLFWwindow* window, ContextConfig config)
    : m_window(window), m_config(config)
{
    // Store this pointer so static callbacks can reach instance methods
    glfwSetWindowUserPointer(m_window, this);

    glfwSetFramebufferSizeCallback(m_window, [](GLFWwindow* w, int width, int height) {
        glViewport(0, 0, width, height);
        auto* ctx = static_cast<Context*>(glfwGetWindowUserPointer(w));
        ctx->m_config.width  = width;
        ctx->m_config.height = height;
        if (ctx->m_resizeCb) ctx->m_resizeCb(width, height);
    });

    glfwSetKeyCallback(m_window, [](GLFWwindow* w, int key, int, int action, int mods) {
        auto* ctx = static_cast<Context*>(glfwGetWindowUserPointer(w));
        if (ctx->m_keyCb) ctx->m_keyCb(key, action, mods);
    });

    glfwSetCursorPosCallback(m_window, [](GLFWwindow* w, double x, double y) {
        auto* ctx = static_cast<Context*>(glfwGetWindowUserPointer(w));
        if (ctx->m_mouseMoveCb) ctx->m_mouseMoveCb(x, y);
    });

    glfwSetScrollCallback(m_window, [](GLFWwindow* w, double dx, double dy) {
        auto* ctx = static_cast<Context*>(glfwGetWindowUserPointer(w));
        if (ctx->m_scrollCb) ctx->m_scrollCb(dx, dy);
    });
}

Context::~Context() {
    if (m_window) {
        glfwDestroyWindow(m_window);
        glfwTerminate();
    }
}

Context::Context(Context&& other) noexcept
    : m_window(other.m_window)
    , m_config(other.m_config)
    , m_resizeCb(std::move(other.m_resizeCb))
    , m_keyCb(std::move(other.m_keyCb))
    , m_mouseMoveCb(std::move(other.m_mouseMoveCb))
    , m_scrollCb(std::move(other.m_scrollCb))
{
    other.m_window = nullptr;
    if (m_window) glfwSetWindowUserPointer(m_window, this);
}

bool  Context::shouldClose()  const { return glfwWindowShouldClose(m_window); }
void  Context::pollEvents()   const { glfwPollEvents(); }
void  Context::swapBuffers()  const { glfwSwapBuffers(m_window); }
void  Context::endFrame()     const { swapBuffers(); pollEvents(); }

void Context::onResize(std::function<void(int,int)> cb)         { m_resizeCb    = std::move(cb); }
void Context::onKey(std::function<void(int,int,int)> cb)        { m_keyCb       = std::move(cb); }
void Context::onMouseMove(std::function<void(double,double)> cb){ m_mouseMoveCb = std::move(cb); }
void Context::onScroll(std::function<void(double,double)> cb)   { m_scrollCb    = std::move(cb); }

} 
