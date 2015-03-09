#ifndef _PRIMITIVE_HPP_
#define _PRIMITIVE_HPP_

#define GLFW_INCLUDE_GLU
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Primitive {
public:
    Primitive(GLfloat* verts, GLfloat* colors, int vertCount);
    virtual ~Primitive();

    virtual void Render();
    void AttachShader(class Shader* shader) {
        this->m_shader = shader;
    }

protected:
    class Shader* m_shader;

    GLuint m_vertexArrayId;
    GLuint m_bufferId;
    GLuint m_colorBufferId;

private:
    Primitive() = delete;
    Primitive(const Primitive& copy) = delete;

};

#endif
