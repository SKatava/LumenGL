// src/renderer/Camera.cpp
#include "lumengl/renderer/Camera.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/constants.hpp>

namespace lgl {

Camera::Camera(CameraConfig config)
    : m_position(config.position)
    , m_fovDeg(config.fovDeg)
    , m_near(config.nearPlane)
    , m_far(config.farPlane)
{
    // Derive initial yaw/pitch from the target vector
    glm::vec3 dir = glm::normalize(config.target - config.position);
    m_yaw   = glm::degrees(std::atan2(dir.z, dir.x));
    m_pitch = glm::degrees(std::asin(dir.y));
    updateVectors();
}

void Camera::setAspect(float aspect) {
    m_aspect = aspect;
}

void Camera::processMouseDelta(float dx, float dy, float sensitivity) {
    m_yaw   += dx * sensitivity;
    m_pitch  -= dy * sensitivity;
    m_pitch   = glm::clamp(m_pitch, -89.f, 89.f);
    updateVectors();
}

void Camera::processScroll(float dy, float speed) {
    m_position += m_front * dy * speed;
}

void Camera::processKeyboard(bool forward, bool back,
                              bool left,    bool right,
                              float dt,     float speed)
{
    glm::vec3 right_vec = glm::normalize(glm::cross(m_front, m_up));
    if (forward) m_position += m_front     * speed * dt;
    if (back)    m_position -= m_front     * speed * dt;
    if (left)    m_position -= right_vec   * speed * dt;
    if (right)   m_position += right_vec   * speed * dt;
}

glm::mat4 Camera::view() const {
    return glm::lookAt(m_position, m_position + m_front, m_up);
}

glm::mat4 Camera::projection() const {
    return glm::perspective(glm::radians(m_fovDeg), m_aspect, m_near, m_far);
}

glm::mat4 Camera::viewProjection() const {
    return projection() * view();
}

void Camera::updateVectors() {
    glm::vec3 front;
    front.x = std::cos(glm::radians(m_yaw)) * std::cos(glm::radians(m_pitch));
    front.y = std::sin(glm::radians(m_pitch));
    front.z = std::sin(glm::radians(m_yaw)) * std::cos(glm::radians(m_pitch));
    m_front = glm::normalize(front);
}

} // namespace lgl
