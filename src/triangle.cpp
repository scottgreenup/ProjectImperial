#define GLFW_INCLUDE_GLU
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <cmath>
#include <iostream>

#include "triangle.hpp"

Triangle::Triangle() {
    GLfloat verts[] = {
        -1.0f, -1.0f, 0.0f,
         1.0f, -1.0f, 0.0f,
         0.0f,  1.0f, 0.0f,
    };

    // generate the colors
    const int vertices = 3;
    GLfloat colors[vertices * 3];

    for (int i = 0; i < vertices; ++i) {
        colors[3 * i + 0] = sinf(i / (float)vertices);
        colors[3 * i + 1] = cosf(i / (float)vertices);
        colors[3 * i + 2] = i / (float)vertices;
    }

    // generate 1 vertex array and store the name in m_vertexArrayId
    glGenVertexArrays(1, &this->m_vertexArrayId);

    // bind to the vertex array with name from m_vertexArrayId
    glBindVertexArray(this->m_vertexArrayId);

    // generate 1 buffer object and store the name in m_bufferId
    glGenBuffers(1, &this->m_bufferId);

    // bind to the buffer object (BO) with name from m_bufferId
    // m_bufferId is now bound to GL_ARRAY_BUFFER
    // GL operations on the target (GL_ARRAY_BUFFER) affect the bound BO
    glBindBuffer(GL_ARRAY_BUFFER, this->m_bufferId);

    // create and initialise the BO's data store
    glBufferData(
        GL_ARRAY_BUFFER, // target
        sizeof(verts),   // size
        verts,           // data
        GL_STATIC_DRAW   // how it will be used
    );

    std::cerr << "Vertex Array ID = " << this->m_vertexArrayId << std::endl;
    std::cerr << "Buffer Object ID = " << this->m_bufferId << std::endl;

    glGenBuffers(1, &this->m_colorBufferId);
    glBindBuffer(GL_ARRAY_BUFFER, this->m_colorBufferId);
    glBufferData(
        GL_ARRAY_BUFFER, // target
        sizeof(colors),   // size
        colors,           // data
        GL_STATIC_DRAW   // how it will be used
    );
}

Triangle::~Triangle() {
    glDeleteBuffers(1, &this->m_bufferId);
    glDeleteVertexArrays(1, &this->m_vertexArrayId);
}

void Triangle::Render() {
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
        1,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
        3,                  // size
        GL_FLOAT,           // type
        GL_FALSE,           // normalized?
        0,                  // stride
        (void*)0            // array buffer offset
    );

    // mode, first, count
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
}

