#ifndef _PRIMITIVE_HPP_
#define _PRIMITIVE_HPP_

#define GLFW_INCLUDE_GLU
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

#include "transform.h"

class Primitive : public Transform {
public:
    Primitive(GLfloat* verts, unsigned int vertCount);
    virtual ~Primitive();

    virtual void Render();

    void AttachShader(class Shader* shader) {
        this->m_shader = shader;
    }

    void ChangeDrawMode(GLenum mode);

    void SetColor(float r, float g, float b);
    void SetOutlineColor(float r, float g, float b);

protected:
    class Shader* m_shader;

    GLuint m_vertexArrayId;
    GLuint m_bufferId;
    GLuint m_normalId;

    GLenum m_drawMode;

    unsigned int m_vertCount;

    glm::vec3 m_color;
    glm::vec3 m_outlineColor;

private:
    Primitive() = delete;
    Primitive(const Primitive& copy) = delete;

};

#endif
