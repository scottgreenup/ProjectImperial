
#include <iostream>

#include "camera.h"

#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

Camera::Camera()
: m_pitch(0)
, m_yaw(0)
, m_free(false) {
    this->m_up = glm::vec3(0, 1, 0);
    this->m_pos = glm::vec3(0, 5, -10);
    this->m_eye = glm::vec3(0, 0, 0);

    this->m_viewMatrix = glm::lookAt(
        this->m_pos, this->m_eye,
        this->m_up
    );
}

Camera::~Camera() {
    
}

void Camera::Update(float dt, float mxDelta, float myDelta) {
    if (m_free) {
        // camera movement:
        //  left and right are square
        //  up and down are foward and backward
        //  the camera therefore looks at a fixed point in front
        //  mouse will rotate up/down left/right
        //  a.k.a Ghost Mode in UT
    } else {
        // camera movement:
        //  left and right will do nothing
        //  up and down are forward and backward / scroll wheel
        //  mouse will rotate up and down, left and right
        //  a.k.a MMO camera

        
    }


    glm::vec3 forward = glm::normalize(this->m_eye - this->m_pos);
    glm::vec3 right = -glm::normalize(glm::cross(glm::vec3(0,1,0), forward));
    //glm::vec3 up = glm::normalize(glm::cross(forward, right));

    float speed = 5.0f;

    if (glfwGetKey(m_window, GLFW_KEY_W) == GLFW_PRESS) {
        m_pos = m_pos + forward * dt * speed;
    }
    if (glfwGetKey(m_window, GLFW_KEY_S) == GLFW_PRESS) {
        m_pos = m_pos - forward * dt * speed;
    }
    if (glfwGetKey(m_window, GLFW_KEY_A) == GLFW_PRESS) {
        m_pos = m_pos - right * dt * speed;
    }
    if (glfwGetKey(m_window, GLFW_KEY_D) == GLFW_PRESS) {
        m_pos = m_pos + right * dt * speed;
    }

    m_eye = m_pos + forward;


    float sensitivity = 0.5f;
    m_pitch += myDelta * sensitivity;

    if (m_pitch < -89.0f) {
        m_pitch = -89.0f;
    } else if (m_pitch > 89.0f) {
        m_pitch = 89.0;
    }

    m_yaw -= mxDelta * sensitivity;

    /*
    */

    // TODO combine into a smaller operation
    glm::quat pan = glm::angleAxis(
        glm::radians(m_yaw),
        glm::vec3(0,1,0)
    );

    glm::quat tilt = glm::angleAxis(
        glm::radians(m_pitch),
        glm::vec3(1,0,0)
    );

    glm::vec3 newForward = tilt * glm::vec3(0,0,1);
              newForward = pan * newForward;

    this->m_eye = this->m_pos + newForward;

    this->m_viewMatrix = glm::lookAt(
        this->m_pos,
        this->m_eye,
        this->m_up
    );
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

