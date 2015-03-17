
#define GLFW_INCLUDE_GLU
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

#include "color.h"

#include "camera.h"
#include "shader.h"
#include "primitive.h"

Primitive::Primitive(GLfloat* verts, GLfloat *colors, unsigned int vertCount)
: Transform()
, m_drawMode(GL_TRIANGLES)
, m_vertCount(vertCount) {

    // generate and use a VAO
    glGenVertexArrays(1, &this->m_vertexArrayId);
    glBindVertexArray(this->m_vertexArrayId);

    // generate and use a VBO
    glGenBuffers(1, &this->m_bufferId);
    glBindBuffer(GL_ARRAY_BUFFER, this->m_bufferId);

    // create and initialise the BO's data store
    glBufferData(
        GL_ARRAY_BUFFER, // target
        sizeof(GLfloat) * vertCount * 3,   // size
        verts,           // data
        GL_STATIC_DRAW   // how it will be used
    );

    glGenBuffers(1, &m_colorBufferId);
    glBindBuffer(GL_ARRAY_BUFFER, m_colorBufferId);
    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(GLfloat) * vertCount * 3,
        colors,
        GL_STATIC_DRAW
    );
}

Primitive::~Primitive() {
    glDeleteBuffers(1, &m_bufferId);
    glDeleteVertexArrays(1, &m_vertexArrayId);
}

void Primitive::ChangeDrawMode(GLenum drawMode) {
    m_drawMode = drawMode;
}

void Primitive::Render() {
    /*
    const int vertices = 36;
    GLfloat colors[vertices * 3];

    for (int i = 0; i < vertices; ++i) {
        float r, g, b;
        HSVtoRGB(
            //(float)(x % 360) + (i / (float)vertices * 360.0f), 
            180.0f * (1.0f + sinf( (this->m_bufferId * 0.00001f) + glfwGetTime() + (1 / (float)vertices * 360.0f))),
            1.0f, 
            1.0f, 
            r, 
            g, 
            b);

        colors[3 * i + 0] = r;
        colors[3 * i + 1] = g;
        colors[3 * i + 2] = b;
    }
    glBindBuffer(GL_ARRAY_BUFFER, this->m_colorBufferId);
    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(GLfloat) * m_vertCount * 3,
        colors,
        GL_STATIC_DRAW
    );
    */

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
    GLfloat* colors = new GLfloat[m_vertCount * 3];
        for (unsigned int i = 0; i < m_vertCount; ++i) {
            colors[3 * i + 0] = 1;
            colors[3 * i + 1] = 1;
            colors[3 * i + 2] = 1;
        }
        glBindBuffer(GL_ARRAY_BUFFER, this->m_colorBufferId);
        glBufferData(
            GL_ARRAY_BUFFER,
            sizeof(GLfloat) * m_vertCount * 3,
            colors,
            GL_STATIC_DRAW
        );
    glBindBuffer(GL_ARRAY_BUFFER, this->m_colorBufferId);
    glVertexAttribPointer(
        1,
        3,
        GL_FLOAT,
        GL_FALSE,
        0,
        (void*)0
    );

    glDrawArrays(m_drawMode, 0, m_vertCount);

    bool draw_outline = true;

    if (draw_outline) {
        glEnableVertexAttribArray(1);
        for (unsigned int i = 0; i < m_vertCount; ++i) {
            colors[3 * i + 0] = 0;
            colors[3 * i + 1] = 0;
            colors[3 * i + 2] = 0;
        }
        glBindBuffer(GL_ARRAY_BUFFER, this->m_colorBufferId);
        glBufferData(
            GL_ARRAY_BUFFER,
            sizeof(GLfloat) * m_vertCount * 3,
            colors,
            GL_STATIC_DRAW
        );
        glBindBuffer(GL_ARRAY_BUFFER, this->m_colorBufferId);
        glVertexAttribPointer(
            1,
            3,
            GL_FLOAT,
            GL_FALSE,
            0,
            (void*)0
        );
        glDrawArrays(GL_LINE_STRIP, 0, m_vertCount);
    }
    delete colors;

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
}
