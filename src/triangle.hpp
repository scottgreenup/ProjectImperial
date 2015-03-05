#ifndef _POLYGON_HPP_
#define _POLYGON_HPP_

class Triangle {

public:
    Triangle();
    ~Triangle();

    void Render();

private:
    Triangle(const Triangle& copy) {};

    GLuint m_vertexArrayId;
    GLuint m_bufferId;
};

#endif
