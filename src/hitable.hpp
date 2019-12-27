#ifndef HITABLE_HPP
#define HITABLE_HPP
#include "ray.hpp"

class material;

struct hit_record {
    // Hit parameter
    float t;
    // Hit point
    vec3 p;
    // Normal vector
    vec3 normal;
    material *mat_ptr;
};

class hitable {
public:
    virtual bool hit(const ray &r, float t_min, float t_max, hit_record &rec) const = 0;
};

#endif