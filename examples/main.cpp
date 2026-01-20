#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <LumenGL/lumen_gl.h>

int main() {
    if (!glfwInit()) {
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glfwWindowHint(GLFW_SAMPLES, 4);

    glfwWindowHint(GLFW_DECORATED, GL_FALSE);


    GLFWwindow* window = glfwCreateWindow(800, 800, "Renderer Example", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwSwapInterval(0);
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {}

    lumen::gl::Renderer renderer;
    renderer.Init();

    lumen::gl::Scene scene("TEST_SCENE");
    scene.AddObject( lumen::gl::RenderObjectBuilder::Create("PYRAMID")
            .WithVertices({
                {{-0.5f, 0.0f,  0.5f}, {0.0f, 0.0f}},
                {{-0.5f, 0.0f, -0.5f}, {5.0f, 0.0f}},
                {{ 0.5f, 0.0f, -0.5f}, {5.0f, 5.0f}},
                {{ 0.5f, 0.0f,  0.5f}, {0.0f, 5.0f}},
                {{ 0.0f, 0.8f,  0.0f}, {2.5f, 5.0f}},
                })
            .WithIndices({
                0,1,2,  0,2,3,     
                0,1,4,  1,2,4,
                2,3,4,  3,0,4     
                })
            .WithProgram(scene.GetOrLoadProgram("...", "...", "DEFAULT_PROGRAM"))
            .WithTexture(scene.GetOrLoadTexture("../assets/textures/white-granite.png"))
            .Build()
    );

    renderer.SetActiveScene(&scene);


    while (!glfwWindowShouldClose(window)) {
        glfwSwapBuffers(window);
        glfwPollEvents();
        renderer.BeginFrame();
        renderer.Render();
        //renderer.EndFrame();main
    }

    glfwTerminate();
    return 0;
}

