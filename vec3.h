#ifndef VEC3_H
#define VEC3_H

#include <math.h>

// Inline member functions need to live in the header file.

class vec3
{
public:
    float x;
    float y;
    float z;

    // Field instantiation syntax.

    vec3() : x(0), y(0), z(0) {}
    vec3(float e0, float e1, float e2) : x(e0), y(e1), z(e2) {}

    // For when color is stored as a vector.

    inline float r() const { return x; }
    inline float g() const { return y; }
    inline float b() const { return z; }

    inline const vec3 &operator+() const { return *this; }
    inline vec3 operator-() const { return vec3(-x, -y, -z); }

    // inline float operator[](int i) const { return e[i]; }
    // inline float &operator[](int i) { return e[i]; }

    inline vec3 &operator+=(const vec3 &v2);
    inline vec3 &operator-=(const vec3 &v2);
    inline vec3 &operator*=(const vec3 &v2);
    inline vec3 &operator/=(const vec3 &v2);
    inline vec3 &operator*=(const float t);
    inline vec3 &operator/=(const float t);

    inline float length() const;
    inline float squared_length() const;

    inline void make_round_int();
    inline void make_unit_vector();
};

#endif