#ifndef _PRIMITIVE_HPP_
#define _PRIMITIVE_HPP_

#define GLFW_INCLUDE_GLU
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

#include "GameObject.h"
#include "Transform.h"
#include "Texture.h"

// goal:
// -- move shader into component
// -- move mesh into component
// -- cube can have mesh, shader, transform
class Primitive : public GameObject {
public:
    Primitive(GLfloat* verts, GLfloat* texCoords, unsigned int vertCount);
    virtual ~Primitive();

    virtual void render() ;

    void AttachShader(class ShaderProgram* shader) {
        this->m_shader = shader;
    }

    void ChangeDrawMode(GLenum mode);

    void SetColor(float r, float g, float b);
    void SetOutlineColor(float r, float g, float b);

protected:
    class ShaderProgram* m_shader;

    GLuint m_vertexArrayId;
    GLuint m_bufferId;
    GLuint m_normalId;
    GLuint m_textureCoordId;

    GLenum m_drawMode;

    unsigned int m_vertCount;

    glm::vec3 m_color;
    glm::vec3 m_outlineColor;

    Texture m_texture;

private:
    Primitive() = delete;
    Primitive(const Primitive& copy) = delete;

};

#endif
