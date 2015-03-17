#define GLFW_INCLUDE_GLU
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

#include "color.h"

#include "camera.h"
#include "shader.h"
#include "centermatrix.h"

CenterMatrix::CenterMatrix(float size)
: Transform()
, m_size(size) {

    GLfloat verts[] = {
        0.0f, 0.0f, 0.0f,
        size, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f,
        0.0f, size, 0.0f,
        0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, size,
    };

    GLfloat colors[] = {
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
    };

    // generate and use a VAO
    glGenVertexArrays(1, &this->m_vertexArrayId);
    glBindVertexArray(this->m_vertexArrayId);

    // generate and use a VBO
    glGenBuffers(1, &this->m_bufferId);
    glBindBuffer(GL_ARRAY_BUFFER, this->m_bufferId);

    // create and initialise the BO's data store
    glBufferData(
        GL_ARRAY_BUFFER, // target
        sizeof(GLfloat) * 18,   // size
        verts,           // data
        GL_STATIC_DRAW   // how it will be used
    );

    glGenBuffers(1, &this->m_colorBufferId);
    glBindBuffer(GL_ARRAY_BUFFER, this->m_colorBufferId);
    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(GLfloat) * 18,
        colors,
        GL_STATIC_DRAW
    );
}

CenterMatrix::~CenterMatrix() {
    glDeleteBuffers(1, &this->m_bufferId);
    glDeleteVertexArrays(1, &this->m_vertexArrayId);
}

void CenterMatrix::Render() {
    this->m_shader->Use();

    GLuint matrixId = glGetUniformLocation(this->m_shader->Id(), "MVP");
    glUniformMatrix4fv(matrixId, 1, GL_FALSE, &MVP()[0][0]);

    glBindVertexArray(this->m_vertexArrayId);
    glEnableVertexAttribArray(0);

    // bind to our buffer object
    glBindBuffer(GL_ARRAY_BUFFER, this->m_bufferId);

    // meta data for the vertices
    glVertexAttribPointer(
        0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
        3,                  // size
        GL_FLOAT,           // type
        GL_FALSE,           // normalized?
        0,                  // stride
        (void*)0            // array buffer offset
    );

    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, this->m_colorBufferId);
    glVertexAttribPointer(
        1,
        3,
        GL_FLOAT,
        GL_FALSE,
        0,
        (void*)0
    );

    glDrawArrays(GL_LINES, 0, 18);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
}
