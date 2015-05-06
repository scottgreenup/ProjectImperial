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

    void AttachShader(class ShaderProgram* shader) {
        this->m_shader = shader;
    }

protected:
    class ShaderProgram* m_shader;

    GLuint m_vertexArrayId;
    GLuint m_bufferId;
    GLuint m_normalBufferId;
    GLuint m_colorBufferId;

private:
    CenterMatrix(const CenterMatrix& copy) = delete;

    float m_size;
};

#endif
