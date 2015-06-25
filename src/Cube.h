#ifndef _CUBE_HPP_
#define _CUBE_HPP_

#include "Primitive.h"

class Cube : public Primitive {
public:
    Cube();
    ~Cube();

    void update() {};

private:
    Cube(const Cube& copy) = delete;

};

#endif
