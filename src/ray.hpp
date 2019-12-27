#ifndef RAY_H
#define RAY_H
#include "vec3.hpp"

class ray
{
public:
    // Initial position
    vec3 A;
    // Direction of the ray
    vec3 B;

    ray() {}
    ray(const vec3 &a, const vec3 &b) : A(a), B(b) {}
    inline vec3 origin() const { return A; }
    inline vec3 direction() const { return B; }
    vec3 point_at_parameter(float t) const { return A + t * B; }
};

#endif