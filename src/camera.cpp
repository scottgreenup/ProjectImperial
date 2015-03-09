#include "camera.hpp"

Camera::Camera()
: m_free(false) {
    this->m_up = glm::vec3(0, 1, 0);
    this->m_pos = glm::vec3(0, 5, -10);
    this->m_eye = glm::vec3(0, 0, 0);

    this->m_viewMatrix = glm::lookAt(
        this->m_pos,
        this->m_eye,
        this->m_up
    );
}

Camera::~Camera() {
    
}

void Camera::LookAt(float x, float y, float z) {
    this->m_eye = glm::vec3(x, y, z);

    this->m_viewMatrix = glm::lookAt(
        this->m_pos,
        this->m_eye,
        this->m_up
    );

    m_free = false;
}

void Camera::Free() {
    m_free = true;
}

void Camera::MoveTo(float x, float y, float z) {
    this->m_pos = glm::vec3(x, y, z);

    this->m_viewMatrix = glm::lookAt(
        this->m_pos,
        this->m_eye,
        this->m_up
    );
}

glm::mat4 Camera::GetViewMatrix() {
    return this->m_viewMatrix;
}

void Camera::SetProjectionMatrix(float angle, float ratio, float near, float far) {
    this->m_projectionMatrix = glm::perspective(angle, ratio, near, far);
}

glm::mat4 Camera::GetProjectionMatrix() {

    return this->m_projectionMatrix;
}

