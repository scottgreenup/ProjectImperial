#ifndef _CUBE_HPP_
#define _CUBE_HPP_

#include "primitive.hpp"

class Cube : public Primitive {
public:
    Cube();
    ~Cube();

    //void Render();

private:
    Cube(const Cube& copy) = delete;

};

#endif