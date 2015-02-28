#include "vector.hpp"

Vector::Vector(float x, float y, float z)
    : x(x)
    , y(y)
    , z(z) {
}

Vector::Vector(const Vector& copy) {
    this->x = copy.x;
    this->y = copy.y;
    this->z = copy.z;
}

Vector::~Vector() { }


