// tests/test_camera.cpp
#include <gtest/gtest.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "lumengl/renderer/Camera.h"

TEST(Camera, DefaultAspectIsSet) {
    lgl::Camera cam(lgl::CameraConfig{
        .position = {0, 0, 5},
        .target   = {0, 0, 0}
    });
    cam.setAspect(16.f / 9.f);

    glm::mat4 proj = cam.projection();
    // Projection matrix should not be identity
    EXPECT_NE(proj, glm::mat4(1.f));
}

TEST(Camera, ViewMatrixPlacesCameraCorrectly) {
    lgl::Camera cam(lgl::CameraConfig{
        .position = {0, 0, 5},
        .target   = {0, 0, 0}
    });

    glm::mat4 view = cam.view();

    // Origin in world space should map close to (0,0,-5) in camera space
    glm::vec4 origin     = glm::vec4(0, 0, 0, 1);
    glm::vec4 inCamSpace = view * origin;

    EXPECT_NEAR(inCamSpace.z, -5.f, 0.01f);
}

TEST(Camera, PositionMatchesConfig) {
    glm::vec3 pos = {3.f, 2.f, 1.f};
    lgl::Camera cam(lgl::CameraConfig{ .position = pos, .target = {0,0,0} });
    EXPECT_NEAR(cam.position().x, pos.x, 1e-5f);
    EXPECT_NEAR(cam.position().y, pos.y, 1e-5f);
    EXPECT_NEAR(cam.position().z, pos.z, 1e-5f);
}

TEST(Camera, SetAspectAffectsProjection) {
    lgl::Camera cam;
    cam.setAspect(1.f);
    glm::mat4 square = cam.projection();

    cam.setAspect(16.f / 9.f);
    glm::mat4 wide = cam.projection();

    // Different aspects should produce different projection matrices
    EXPECT_NE(square[0][0], wide[0][0]);
}

TEST(Camera, ScrollMovesPosition) {
    lgl::Camera cam(lgl::CameraConfig{
        .position = {0, 0, 5},
        .target   = {0, 0, 0}
    });
    glm::vec3 before = cam.position();
    cam.processScroll(1.f);
    glm::vec3 after = cam.position();

    EXPECT_NE(before.z, after.z);
}
