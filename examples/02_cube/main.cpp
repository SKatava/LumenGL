// examples/02_cube/main.cpp
#include <lumengl/lumengl.h>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>

int main() {
    auto ctxResult = lgl::Context::create({ .width=1280, .height=720, .title="LumenGL — Cube" });
    if (ctxResult.isErr()) { fprintf(stderr, "%s\n", ctxResult.error().c_str()); return 1; }
    lgl::Context& ctx = ctxResult.value();

    auto shaderResult = lgl::ShaderProgram::fromFiles(
        "shaders/default.vert", "shaders/default.frag"
    );
    if (shaderResult.isErr()) { fprintf(stderr, "%s\n", shaderResult.error().c_str()); return 1; }
    lgl::ShaderProgram& shader = shaderResult.value();

    lgl::Texture texture = lgl::Texture::createWhite();
    auto texResult = lgl::Texture::fromFile("/home/skatava/Projects/holder/examples/02_cube/assets/white-granite.png");
    if (texResult.isOk()) texture = std::move(texResult.value());
    lgl::Mesh     cube     = lgl::Mesh::cube();
    lgl::Material material = { &shader, &texture, {1.f, 1.f, 1.f, 1.f} };

    lgl::Camera camera(lgl::CameraConfig{
        .position = { 0.f, 1.f, 3.f },
        .target   = { 0.f, 0.f, 0.f }
    });
    camera.setAspect(ctx.aspectRatio());

    lgl::Renderer renderer;
    renderer.setClearColor(0.05f, 0.05f, 0.05f);

    ctx.onResize([&](int w, int h) {
        camera.setAspect(static_cast<float>(w) / static_cast<float>(h));
    });

    double lastX = 640, lastY = 360;
    bool   firstMouse = true;
    bool   mouseDown  = false;

    ctx.onMouseMove([&](double x, double y) {
        if (!mouseDown) return;
        if (firstMouse) { lastX = x; lastY = y; firstMouse = false; }
        camera.processMouseDelta(
            static_cast<float>(x - lastX),
            static_cast<float>(y - lastY)
        );
        lastX = x; lastY = y;
    });

    ctx.onScroll([&](double, double dy) {
        camera.processScroll(static_cast<float>(dy));
    });

    ctx.onKey([&](int key, int action, int) {
        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
            glfwSetWindowShouldClose(ctx.handle(), true);
        if (key == GLFW_MOUSE_BUTTON_LEFT) 
            mouseDown = (action == GLFW_PRESS);
    });

    float rotation = 0.f;
    float lastTime = static_cast<float>(glfwGetTime());

    while (!ctx.shouldClose()) {
        float now = static_cast<float>(glfwGetTime());
        float dt  = now - lastTime;
        lastTime  = now;

        rotation += 45.f * dt; 

        glm::mat4 model = glm::rotate(
            glm::mat4(1.f),
            glm::radians(rotation),
            glm::vec3(0.f, 1.f, 0.f)
        );

        // Keyboard movement
        camera.processKeyboard(
            glfwGetKey(ctx.handle(), GLFW_KEY_W) == GLFW_PRESS,
            glfwGetKey(ctx.handle(), GLFW_KEY_S) == GLFW_PRESS,
            glfwGetKey(ctx.handle(), GLFW_KEY_A) == GLFW_PRESS,
            glfwGetKey(ctx.handle(), GLFW_KEY_D) == GLFW_PRESS,
            dt
        );

        renderer.beginFrame();
        renderer.submit({ &cube, &material, model });
        renderer.flush(camera);
        ctx.endFrame();
    }

    return 0;
}
