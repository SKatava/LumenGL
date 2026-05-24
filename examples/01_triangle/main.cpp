// examples/01_triangle/main.cpp
#include <lumengl/lumengl.h>

int main() {
    // 1. Context first — always
    auto ctxResult = lgl::Context::create({ .width=1920, .height=720 });
    if (ctxResult.isErr()) {
        fprintf(stderr, "%s\n", ctxResult.error().c_str());
        return 1;
    }
    lgl::Context& ctx = ctxResult.value();

    // 2. Shader
    auto shaderResult = lgl::ShaderProgram::fromFiles(
        "shaders/triangle.vert", "shaders/triangle.frag"
    );
    if (shaderResult.isErr()) {
        fprintf(stderr, "%s\n", shaderResult.error().c_str());
        return 1;
    }
    lgl::ShaderProgram& shader = shaderResult.value();

    // 3. Geometry and material
    lgl::Mesh     quad     = lgl::Mesh::quad();
    lgl::Texture  white    = lgl::Texture::createWhite();
    lgl::Material material = { &shader, &white, {1.f, 0.5f, 0.2f, 1.f} };

    // 4. Camera and renderer
    lgl::Camera   camera({ .position={0,0,3} });
    lgl::Renderer renderer;

    ctx.onResize([&](int w, int h) {
        glViewport(0, 0, w, h);
        camera.setAspect(static_cast<float>(w) / static_cast<float>(h));
    });

    // 5. Main loop — correct order, no surprises
    while (!ctx.shouldClose()) {
        renderer.beginFrame();

        renderer.submit({ &quad, &material, glm::mat4(1.f) });
        renderer.flush(camera);

        ctx.endFrame(); // swap then poll
    }

    return 0;
}
