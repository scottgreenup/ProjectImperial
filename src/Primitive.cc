
#define GLFW_INCLUDE_GLU
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <stdio.h>
#include <string>
#include <iostream>

#include "Color.h"

#include "Camera.h"
#include "ShaderProgram.h"
#include "Primitive.h"

GLfloat* normals = nullptr;

Primitive::Primitive(GLfloat* verts, GLfloat* texCoords, unsigned int vertCount)
: m_drawMode(GL_TRIANGLES)
, m_vertCount(vertCount)
, m_texture("cube.jpg") {

    this->addComponent(new Transform());

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

    // TODO improve the normals being calculated, should be moved to the class above?
    normals = new GLfloat[vertCount * 3];
    for (unsigned int i = 0; i < (vertCount / 3); i++) {
        glm::vec3 a(
            verts[9 * i + 0],
            verts[9 * i + 1],
            verts[9 * i + 2]
        );
        glm::vec3 b(
            verts[9 * i + 3],
            verts[9 * i + 4],
            verts[9 * i + 5]
        );
        glm::vec3 c(
            verts[9 * i + 6],
            verts[9 * i + 7],
            verts[9 * i + 8]
        );

        glm::vec3 edgeAB = b - a;
        glm::vec3 edgeAC = c - a;

        glm::vec3 normal = -glm::cross(edgeAB, edgeAC);
        normals[9 * i + 0] = normal.x;
        normals[9 * i + 1] = normal.y;
        normals[9 * i + 2] = normal.z;
        normals[9 * i + 3] = normal.x;
        normals[9 * i + 4] = normal.y;
        normals[9 * i + 5] = normal.z;
        normals[9 * i + 6] = normal.x;
        normals[9 * i + 7] = normal.y;
        normals[9 * i + 8] = normal.z;
    }

    glGenBuffers(1, &this->m_normalId);
    glBindBuffer(GL_ARRAY_BUFFER, this->m_normalId);
    glBufferData(
        GL_ARRAY_BUFFER, // target
        sizeof(GLfloat) * vertCount * 3,   // size
        normals,         // data
        GL_STATIC_DRAW   // how it will be used
    );

    glGenBuffers(1, &this->m_textureCoordId);
    glBindBuffer(GL_ARRAY_BUFFER, this->m_textureCoordId);
    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(GLfloat) * vertCount * 2,
        texCoords,
        GL_STATIC_DRAW
    );
}

Primitive::~Primitive() {
    delete normals;

    glDeleteBuffers(1, &m_textureCoordId);
    glDeleteBuffers(1, &m_normalId);
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

void Primitive::render() {
    this->m_shader->use();

    GLuint modelViewId  = glGetUniformLocation(this->m_shader->id(), "modelView");
    GLuint normalId     = glGetUniformLocation(this->m_shader->id(), "normalMatrix");
    GLuint projectionId = glGetUniformLocation(this->m_shader->id(), "projection");
    GLuint colorId      = glGetUniformLocation(this->m_shader->id(), "solidColor");

    Transform* t = this->getComponent<Transform>();

    glUniformMatrix4fv(modelViewId, 1, GL_FALSE, &t->ModelView()[0][0]);
    glUniformMatrix4fv(normalId, 1, GL_FALSE, &(glm::transpose(glm::inverse(t->Model()))[0][0]));
    glUniformMatrix4fv(projectionId, 1, GL_FALSE, &Camera::Get().GetProjectionMatrix()[0][0]);
    glUniform3fv(colorId, 1, glm::value_ptr(m_color));

    GLuint fogColorId   = glGetUniformLocation(m_shader->id(), "fogParams.color");
    GLuint fogStartId   = glGetUniformLocation(m_shader->id(), "fogParams.start");
    GLuint fogEndId     = glGetUniformLocation(m_shader->id(), "fogParams.end");
    GLuint fogDensityId = glGetUniformLocation(m_shader->id(), "fogParams.density");

    glUniform1f(fogStartId, 10.0f);
    glUniform1f(fogEndId, 500.0f);
    glUniform1f(fogDensityId, 0.05f);
    glUniform4f(fogColorId, 0.1f, 0.1f, 0.1f, 1.0f);

    glBindVertexArray(this->m_vertexArrayId);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, this->m_bufferId);
    glVertexAttribPointer(
        0,                  // attribute 0.s No particular reason for 0, but must match the layout in the shader.
        3,                  // size of each vert
        GL_FLOAT,           // type
        GL_FALSE,           // normalized?
        0,                  // stride
        (void*)0            // array buffer offset
    );
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, this->m_normalId);
    glVertexAttribPointer(
        1,                  // attribute 0.s No particular reason for 0, but must match the layout in the shader.
        3,                  // size of each vert
        GL_FLOAT,           // type
        GL_FALSE,           // normalized?
        0,                  // stride
        (void*)0            // array buffer offset
    );
    glEnableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER, this->m_textureCoordId);
    glVertexAttribPointer(
        2,                  // attribute 0.s No particular reason for 0, but must match the layout in the shader.
        2,                  // size of each vert
        GL_FLOAT,           // type
        GL_TRUE,            // normalized?
        0,                  // stride
        (void*)0            // array buffer offset
    );

    // texture stuff
    int samplerId = glGetUniformLocation(this->m_shader->id(), "tex");
    glUniform1i(samplerId, 0);
    m_texture.bind();

    glDrawArrays(m_drawMode, 0, m_vertCount);

    bool draw_outline = false;
    if (draw_outline) {
        glUniform3fv(colorId, 1, glm::value_ptr(m_outlineColor));
        glDrawArrays(GL_LINE_STRIP, 0, m_vertCount);
    }

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
}

