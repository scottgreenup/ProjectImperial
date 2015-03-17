#ifndef _PRIMITIVE_HPP_
#define _PRIMITIVE_HPP_

#define GLFW_INCLUDE_GLU
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

#include "transform.h"

class Primitive : public Transform {
public:
    Primitive(GLfloat* verts, GLfloat* colors, unsigned int vertCount);
    virtual ~Primitive();

    virtual void Render();

    void AttachShader(class Shader* shader) {
        this->m_shader = shader;
    }

    void ChangeDrawMode(GLenum mode);

protected:
    class Shader* m_shader;

    GLuint m_vertexArrayId;
    GLuint m_bufferId;
    GLuint m_colorBufferId;

    GLenum m_drawMode;

    unsigned int m_vertCount;

private:
    Primitive() = delete;
    Primitive(const Primitive& copy) = delete;

};

#endif
