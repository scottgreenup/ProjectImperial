#ifndef _CUBE_HPP_
#define _CUBE_HPP_

class Cube {
public:
    Cube();
    ~Cube();

    void Render();

private:
    Cube(const Cube& copy) { (void)copy; };

    GLuint m_vertexArrayId;
    GLuint m_bufferId;
    GLuint m_colorBufferId;
};

#endif
