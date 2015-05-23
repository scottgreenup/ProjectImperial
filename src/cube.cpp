#define GLFW_INCLUDE_GLU
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <cmath>
#include <iostream>

#include "color.h"
#include "cube.h"

GLfloat verts[] = {
    -0.5f, -0.5f, -0.5f,
    -0.5f, -0.5f,  0.5f,
    -0.5f,  0.5f,  0.5f,

     0.5f,  0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,
    -0.5f,  0.5f, -0.5f,

     0.5f, -0.5f,  0.5f,
    -0.5f, -0.5f, -0.5f,
     0.5f, -0.5f, -0.5f, 

     0.5f,  0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,

    -0.5f, -0.5f, -0.5f,
    -0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f, -0.5f,

     0.5f, -0.5f,  0.5f,
    -0.5f, -0.5f,  0.5f,
    -0.5f, -0.5f, -0.5f,

    -0.5f,  0.5f,  0.5f,
    -0.5f, -0.5f,  0.5f,
     0.5f, -0.5f,  0.5f,

     0.5f,  0.5f,  0.5f,
     0.5f, -0.5f, -0.5f,
     0.5f,  0.5f, -0.5f,

     0.5f, -0.5f, -0.5f,
     0.5f,  0.5f,  0.5f,
     0.5f, -0.5f,  0.5f,

     0.5f,  0.5f,  0.5f,
     0.5f,  0.5f, -0.5f,
    -0.5f,  0.5f, -0.5f,

     0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f, -0.5f,
    -0.5f,  0.5f,  0.5f,

     0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f,  0.5f,
     0.5f, -0.5f,  0.5f
};

GLfloat texcoords[] = {
    0.0f, 0.0f,     //a
    1.0f, 0.0f,     //b
    1.0f, 1.0f,     //c

    0.0f, 1.0f,     //e
    1.0f, 0.0f,     //a
    1.0f, 1.0f,     //d

    1.0f, 1.0f, //g
    0.0f, 0.0f, //a
    1.0f, 0.0f, //h

    0.0f, 1.0f,     //e
    0.0f, 0.0f,     //h
    1.0f, 0.0f,     //a

    0.0f, 0.0f,     //a
    1.0f, 1.0f,     //c
    0.0f, 1.0f,     //d

    1.0f, 1.0f, //g
    0.0f, 1.0f, //b
    0.0f, 0.0f, //a

    0.0f, 1.0f, //c
    0.0f, 0.0f, //b
    1.0f, 0.0f, //g

    0.0f, 1.0f, //f
    1.0f, 0.0f, //h
    1.0f, 1.0f, //e

    1.0f, 0.0f, //h
    0.0f, 1.0f, //f
    0.0f, 0.0f, //g

    1.0f, 0.0f, //f
    1.0f, 1.0f, //e
    0.0f, 1.0f, //d

    1.0f, 0.0f, //f
    0.0f, 1.0f, //d
    0.0f, 0.0f, //c

    1.0f, 1.0f, //f
    0.0f, 1.0f, //c
    1.0f, 0.0f  //g
};

Cube::Cube()
: Primitive(&verts[0], &texcoords[0], (sizeof(verts) / sizeof(GLfloat) / 3)) {
    this->SetColor(1.0f, 0.0f, 0.0f);
    this->SetOutlineColor(0.0f, 1.0f, 0.0f);
}

Cube::~Cube() { }
