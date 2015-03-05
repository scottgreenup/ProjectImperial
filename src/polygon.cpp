#define GLFW_INCLUDE_GLU
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <cmath>
#include <iostream>

#include "polygon.hpp"

Polygon::Polygon() {
    glGenVertexArrays(1, &this->m_uiVertexArrayId);
    glBindVertexArray(this->m_uiVertexArrayId);

    GLfloat verts[] = {
        -1.0f, -1.0f, 0.0f,
         1.0f, -1.0f, 0.0f,
         0.0f,  1.0f, 0.0f,
    };

    glGenBuffers(1, &this->m_uiVertexBuffer);

    glBindBuffer(
        GL_ARRAY_BUFFER, 
        this->m_uiVertexBuffer
    );

    glBufferData(
        GL_ARRAY_BUFFER, 
        sizeof(verts), 
        verts,
        GL_STATIC_DRAW
    );

    std::cerr << "m_uiVertexArrayId = " << this->m_uiVertexArrayId << std::endl;
    std::cerr << "m_uiVertexBuffer = " << this->m_uiVertexBuffer << std::endl;
}

Polygon::~Polygon() {
    glDeleteBuffers(1, &this->m_uiVertexBuffer);
    glDeleteVertexArrays(1, &this->m_uiVertexArrayId);
}

void Polygon::Render() {
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, this->m_uiVertexBuffer);
    glVertexAttribPointer(
        0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
        3,                  // size
        GL_FLOAT,           // type
        GL_FALSE,           // normalized?
        0,                  // stride
        (void*)0            // array buffer offset
    );

    glDrawArrays(GL_TRIANGLES, 0, 3);
    glDisableVertexAttribArray(0);
}
