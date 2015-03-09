
#define GLFW_INCLUDE_GLU
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

#include "color.h"

#include "camera.h"
#include "shader.h"
#include "primitive.h"

Primitive::Primitive(GLfloat* verts, GLfloat *colors, int vertCount)
: position(glm::vec3(0.0f))
, eulerAngles(glm::vec3(0.0f))
, scale(glm::vec3(1.0f)) {

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

    std::cerr << "Vertex Array ID = " << this->m_vertexArrayId << std::endl;
    std::cerr << "Buffer Object ID = " << this->m_bufferId << std::endl;

    glGenBuffers(1, &this->m_colorBufferId);
    glBindBuffer(GL_ARRAY_BUFFER, this->m_colorBufferId);
    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(GLfloat) * vertCount * 3,
        colors,
        GL_STATIC_DRAW
    );
}

Primitive::~Primitive() {
    glDeleteBuffers(1, &this->m_bufferId);
    glDeleteVertexArrays(1, &this->m_vertexArrayId);
}

void Primitive::Render() {
    // each triangle needs 3 verts and each vert needs 3 coordinates
    
    const int vertices = 36;
    GLfloat colors[vertices * 3];

    for (int i = 0; i < vertices; ++i) {
        float r, g, b;
        HSVtoRGB(
            //(float)(x % 360) + (i / (float)vertices * 360.0f), 
            180.0f * (1.0f + sinf(this->m_bufferId + glfwGetTime() + (1 / (float)vertices * 360.0f))),
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
        sizeof(GLfloat) * 36 * 3,
        colors,
        GL_STATIC_DRAW
    );

    this->m_shader->Use();

    GLuint matrixId = glGetUniformLocation(this->m_shader->Id(), "MVP");
    glm::mat4 projection = Camera::Get()->GetProjectionMatrix();
    glm::mat4 view = Camera::Get()->GetViewMatrix();

    glm::mat4 model = glm::translate(glm::mat4(1.0f), this->position);
    model = glm::rotate(model, this->eulerAngles.x, glm::vec3(1,0,0));
    model = glm::rotate(model, this->eulerAngles.y, glm::vec3(0,1,0));
    model = glm::rotate(model, this->eulerAngles.z, glm::vec3(0,0,1));
    model = glm::scale(model, this->scale);

    glm::mat4 mvp = projection * view * model;
    glUniformMatrix4fv(matrixId, 1, GL_FALSE, &mvp[0][0]);

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

    glDrawArrays(GL_TRIANGLES, 0, 12*3);
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
}
