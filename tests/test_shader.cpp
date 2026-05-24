// tests/test_shader.cpp
#include <gtest/gtest.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "lumengl/gpu/ShaderProgram.h"

// Fixture that creates a headless GL context for GPU tests
class GLTest : public ::testing::Test {
protected:
    void SetUp() override {
        glfwInit();
        glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE); // headless
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        m_window = glfwCreateWindow(1, 1, "", nullptr, nullptr);
        glfwMakeContextCurrent(m_window);
        gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress));
    }

    void TearDown() override {
        glfwDestroyWindow(m_window);
        glfwTerminate();
    }

    GLFWwindow* m_window {nullptr};
};

const char* VALID_VERT = R"(
#version 460 core
layout(location = 0) in vec3 a_position;
void main() { gl_Position = vec4(a_position, 1.0); }
)";

const char* VALID_FRAG = R"(
#version 460 core
out vec4 FragColor;
void main() { FragColor = vec4(1.0); }
)";

const char* INVALID_FRAG = R"(
#version 460 core
out vec4 FragColor;
void main() { FragColor = vec4(UNDEFINED_VAR); }
)";

TEST_F(GLTest, ValidShaderCompilesSuccessfully) {
    auto result = lgl::ShaderProgram::fromSource(VALID_VERT, VALID_FRAG);
    EXPECT_TRUE(result.isOk()) << result.error();
}

TEST_F(GLTest, InvalidShaderReturnsError) {
    auto result = lgl::ShaderProgram::fromSource(VALID_VERT, INVALID_FRAG);
    EXPECT_TRUE(result.isErr());
    EXPECT_FALSE(result.error().empty());
}

TEST_F(GLTest, ShaderMoveTransfersOwnership) {
    auto result = lgl::ShaderProgram::fromSource(VALID_VERT, VALID_FRAG);
    ASSERT_TRUE(result.isOk());

    lgl::ShaderProgram a = std::move(result).value();
    GLuint originalId    = a.id();

    lgl::ShaderProgram b = std::move(a);

    EXPECT_EQ(b.id(), originalId);  // b has the ID
    EXPECT_EQ(a.id(), 0u);          // a was zeroed
}

TEST_F(GLTest, ShaderIdIsNonZeroAfterCompile) {
    auto result = lgl::ShaderProgram::fromSource(VALID_VERT, VALID_FRAG);
    ASSERT_TRUE(result.isOk());
    EXPECT_NE(result.value().id(), 0u);
}
