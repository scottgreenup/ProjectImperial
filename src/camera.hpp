#ifndef _CAMERA_HPP_
#define _CAMERA_HPP_

#define GLFW_INCLUDE_GLU
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
public:
    Camera();
    ~Camera();

    static Camera* Get() {
        static Camera* instance;

        if (instance == 0) {
            instance = new Camera();
        }   

        return instance;
    }

    void SetWindow(GLFWwindow* window) {
        m_window = window;
    }

    void Free();

    void LookAt(float x, float y, float z);
    void MoveTo(float x, float y, float z);

    glm::vec3 Forward() {
        return glm::normalize(this->m_pos - this->m_eye);
    }

    void SetProjectionMatrix(float angle, float ratio, float near, float far);

    glm::mat4 GetViewMatrix();
    glm::mat4 GetProjectionMatrix();

private:
    Camera(const Camera& copy);

    GLFWwindow* m_window;

    glm::mat4 m_viewMatrix;
    glm::mat4 m_projectionMatrix;

    glm::vec3 m_eye;
    glm::vec3 m_pos;
    glm::vec3 m_up;

    bool m_free;
};

//GLFWwindow* Camera::m_window = 0;

#endif
