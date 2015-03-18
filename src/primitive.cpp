
#define GLFW_INCLUDE_GLU
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

#include "color.h"

#include "camera.h"
#include "shader.h"
#include "primitive.h"

Primitive::Primitive(GLfloat* verts, unsigned int vertCount)
: Transform()
, m_drawMode(GL_TRIANGLES)
, m_vertCount(vertCount) {

    // generate and use a VAO
    glGenVertexArrays(1, &this->m_vertexArrayId);
    glBindVertexArray(this->m_vertexArrayId);

    // generate and use a VBO
    glGenBuffers(1, &this->m_bufferId);
    glBindBuffer(GL_ARRAY_BUFFER, this->m_bufferId);
    glBufferData(
        GL_ARRAY_BUFFER, // target
        sizeof(GLfloat) * vertCount * 3,   // size
        verts,           // data
        GL_STATIC_DRAW   // how it will be used
    );
}

Primitive::~Primitive() {
    glDeleteBuffers(1, &m_bufferId);
    glDeleteVertexArrays(1, &m_vertexArrayId);
}

void Primitive::ChangeDrawMode(GLenum drawMode) {
    m_drawMode = drawMode;
}

void Primitive::SetOutlineColor(float r, float g, float b) {
    m_outlineColor = glm::vec3(r, g, b);
}

void Primitive::SetColor(float r, float g, float b) {
    m_color = glm::vec3(r, g, b);
}

void Primitive::Render() {
    this->m_shader->Use();

    GLuint matrixId = glGetUniformLocation(this->m_shader->Id(), "MVP");
    GLuint colorId = glGetUniformLocation(this->m_shader->Id(), "solidColor");

    glUniformMatrix4fv(matrixId, 1, GL_FALSE, &MVP()[0][0]);
    glUniform3fv(colorId, 1, glm::value_ptr(m_color));

    glBindVertexArray(this->m_vertexArrayId);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, this->m_bufferId);
    glVertexAttribPointer(
        0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
        3,                  // size of each vert
        GL_FLOAT,           // type
        GL_FALSE,           // normalized?
        0,                  // stride
        (void*)0            // array buffer offset
    );

    glDrawArrays(m_drawMode, 0, m_vertCount);

    bool draw_outline = true;
    if (draw_outline) {
        glUniform3fv(colorId, 1, glm::value_ptr(m_outlineColor));
        glDrawArrays(GL_LINE_STRIP, 0, m_vertCount);
    }

    glDisableVertexAttribArray(0);
}
