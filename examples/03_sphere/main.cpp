// examples/03_planet/main.cpp
#include <lumengl/lumengl.h>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>

int main() {
    auto ctxResult = lgl::Context::create({
        .width=1280, .height=720, .title="Sphere"
    });
    if (ctxResult.isErr()) { fprintf(stderr, "%s\n", ctxResult.error().c_str()); return 1; }
    lgl::Context& ctx = ctxResult.value();

    auto shaderResult = lgl::ShaderProgram::fromFiles(
        "shaders/default.vert", "shaders/default.frag"
    );
    if (shaderResult.isErr()) { fprintf(stderr, "%s\n", shaderResult.error().c_str()); return 1; }
    lgl::ShaderProgram& shader = shaderResult.value();

    auto texResult = lgl::Texture::fromFile("/home/skatava/Projects/holder/examples/03_sphere/assets/earth.png");
    if (texResult.isErr()) { fprintf(stderr, "%s\n", texResult.error().c_str()); return 1; }
    lgl::Texture& texture = texResult.value();

    lgl::Mesh     sphere   = lgl::Mesh::icosphere(4);
    lgl::Material material = { &shader, &texture, {1.f, 1.f, 1.f, 1.f} };

    lgl::Camera camera(lgl::CameraConfig{
        .position = { 0.f, 0.f, 3.f },
        .target   = { 0.f, 0.f, 0.f }
    });
    camera.setAspect(ctx.aspectRatio());

    lgl::Renderer renderer;
    renderer.setClearColor(0.0f, 0.0f, 0.0f); 

    ctx.onResize([&](int w, int h) {
        camera.setAspect(static_cast<float>(w) / static_cast<float>(h));
    });

    ctx.onScroll([&](double, double dy) {
        camera.processScroll(static_cast<float>(dy), 0.3f);
    });

    ctx.onKey([&](int key, int action, int) {
        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
            glfwSetWindowShouldClose(ctx.handle(), true);
    });

    float rotation = 0.f;
    float lastTime = static_cast<float>(glfwGetTime());

    while (!ctx.shouldClose()) {
        float now = static_cast<float>(glfwGetTime());
        float dt  = now - lastTime;
        lastTime  = now;

        rotation += 15.f * dt; 

        glm::mat4 model = glm::rotate(
            glm::mat4(1.f),
            glm::radians(rotation),
            glm::vec3(0.f, 1.f, 0.f)
        );

        camera.processKeyboard(
            glfwGetKey(ctx.handle(), GLFW_KEY_W) == GLFW_PRESS,
            glfwGetKey(ctx.handle(), GLFW_KEY_S) == GLFW_PRESS,
            glfwGetKey(ctx.handle(), GLFW_KEY_A) == GLFW_PRESS,
            glfwGetKey(ctx.handle(), GLFW_KEY_D) == GLFW_PRESS,
            dt, 2.f
        );

        renderer.beginFrame();
        renderer.submit({ &sphere, &material, model });
        renderer.flush(camera);
        ctx.endFrame();
    }

    return 0;
}
