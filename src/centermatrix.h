#ifndef _CENTERMATRIX_HPP_
#define _CENTERMATRIX_HPP_

#define GLFW_INCLUDE_GLU
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

#include "transform.h"

class CenterMatrix : public Transform {
public:
    CenterMatrix(float size);
    virtual ~CenterMatrix();

    virtual void Render();

    void AttachShader(class Shader* shader) {
        this->m_shader = shader;
    }

protected:
    class Shader* m_shader;

    GLuint m_vertexArrayId;
    GLuint m_bufferId;
    GLuint m_normalBufferId;

private:
    CenterMatrix(const CenterMatrix& copy) = delete;

    float m_size;
};

#endif
