// include/lumengl/renderer/Camera.h
#pragma once
#include <glm/glm.hpp>

namespace lgl {

// Moved outside Camera — fixes GCC's incomplete-type default argument restriction
struct CameraConfig {
    glm::vec3 position  { 0.f, 0.f, 5.f };
    glm::vec3 target    { 0.f, 0.f, 0.f };
    float     fovDeg    { 45.f };
    float     nearPlane { 0.1f };
    float     farPlane  { 1000.f };
};

class Camera {
public:
    explicit Camera(CameraConfig config = CameraConfig{});

    void setAspect(float aspect);

    void processMouseDelta(float dx, float dy, float sensitivity = 0.1f);
    void processScroll(float dy, float speed = 2.f);
    void processKeyboard(bool forward, bool back,
                         bool left,    bool right,
                         float dt,     float speed = 5.f);

    [[nodiscard]] glm::mat4 view()           const;
    [[nodiscard]] glm::mat4 projection()     const;
    [[nodiscard]] glm::mat4 viewProjection() const;
    [[nodiscard]] glm::vec3 position()       const noexcept { return m_position; }

private:
    glm::vec3 m_position;
    glm::vec3 m_front   { 0.f, 0.f, -1.f };
    glm::vec3 m_up      { 0.f, 1.f,  0.f };

    float m_yaw      { -90.f };
    float m_pitch    {   0.f };
    float m_fovDeg;
    float m_aspect   { 16.f / 9.f };
    float m_near;
    float m_far;

    void updateVectors();
};

} // namespace lgl
