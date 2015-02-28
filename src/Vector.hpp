#ifndef _VECTOR_HPP_
#define _VECTOR_HPP_

class Vector {
public:
    Vector(float x, float y, float z);
    Vector(const Vector &copy);
    ~Vector();

    float x;
    float y;
    float z;
};

#endif
