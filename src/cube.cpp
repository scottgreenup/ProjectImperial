#define GLFW_INCLUDE_GLU
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <cmath>
#include <iostream>

#include "color.hpp"
#include "cube.hpp"

Cube::Cube() {

    GLfloat verts[] = {
        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
         1.0f,  1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
         1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f, -1.0f,
         1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f, -1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
         1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
         1.0f, -1.0f,  1.0f
    };

    // each triangle needs 3 verts and each vert needs 3 coordinates
    const int vertices = 36;
    GLfloat colors[vertices * 3];

    for (int i = 0; i < vertices; ++i) {

        float r, g, b;
        HSVtoRGB((i / (float)vertices * 360.0f), 1.0f, 1.0f, r, g, b);

        colors[3 * i + 0] = r;
        colors[3 * i + 1] = g;
        colors[3 * i + 2] = b;
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
        GL_ARRAY_BUFFER,
        sizeof(colors),
        colors,
        GL_STATIC_DRAW
    );

}

Cube::~Cube() {
    glDeleteBuffers(1, &this->m_bufferId);
    glDeleteVertexArrays(1, &this->m_vertexArrayId);
}

void Cube::Render() {
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
    // mode, first, count
    glDrawArrays(GL_TRIANGLES, 0, 12*3);
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
}
