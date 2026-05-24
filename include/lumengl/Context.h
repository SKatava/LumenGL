// include/lumengl/Context.h
#pragma once
#include <string>
#include <functional>
#include "util/Result.h"

struct GLFWwindow;

namespace lgl {

struct ContextConfig {
    int         width       {1280};
    int         height      {720};
    std::string title       {"LumenGL"};
    bool        vsync       {true};
    int         msaaSamples {4};
    int         glMajor     {4};
    int         glMinor     {6};
};

class Context {
public:
    // Factory — only way to create a context
    // Returns error string if GLFW or GLAD initialization fails
    [[nodiscard]]
    static Result<Context> create(ContextConfig config = {});

    ~Context();

    // Non-copyable, movable
    Context(const Context&)            = delete;
    Context& operator=(const Context&) = delete;
    Context(Context&&)                 noexcept;
    Context& operator=(Context&&)      noexcept;

    [[nodiscard]] bool shouldClose()   const;
    void               pollEvents()    const;
    void               swapBuffers()   const;

    // Convenience — poll + swap in correct order
    void               endFrame()      const;

    [[nodiscard]] int  width()         const noexcept { return m_config.width; }
    [[nodiscard]] int  height()        const noexcept { return m_config.height; }
    [[nodiscard]] float aspectRatio()  const noexcept {
        return static_cast<float>(m_config.width) / static_cast<float>(m_config.height);
    }

    [[nodiscard]] GLFWwindow* handle() const noexcept { return m_window; }

    // Callback registration
    void onResize(std::function<void(int w, int h)> cb);
    void onKey(std::function<void(int key, int action, int mods)> cb);
    void onMouseMove(std::function<void(double x, double y)> cb);
    void onScroll(std::function<void(double dx, double dy)> cb);

private:
    explicit Context(GLFWwindow* window, ContextConfig config);

    GLFWwindow*   m_window {nullptr};
    ContextConfig m_config;

    std::function<void(int, int)>         m_resizeCb;
    std::function<void(int, int, int)>    m_keyCb;
    std::function<void(double, double)>   m_mouseMoveCb;
    std::function<void(double, double)>   m_scrollCb;
};

} 
