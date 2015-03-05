#ifndef _POLYGON_HPP_
#define _POLYGON_HPP_

class Polygon {

public:
    Polygon();
    ~Polygon();

    void Render();

private:
    Polygon(const Polygon& copy) {};

    GLuint m_uiVertexArrayId;
    GLuint m_uiVertexBuffer;
};

#endif
