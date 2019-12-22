#include "vec3.h"
#include <math.h>
#include <stdlib.h>
#include <iostream>

// Inline pure functions can live in implementation files.

inline std::istream &operator>>(std::istream &is, vec3 &t)
{
    is >> t.e[0] >> t.e[1] >> t.e[2];
    return is;
}

inline std::ostream &operator<<(std::ostream &os, const vec3 &t)
{
    os << t.x() << " " << t.y() << " " << t.z();
    return os;
}

inline void vec3::make_unit_vector()
{
    float k = 1.0 / length();
    e[0] *= k;
    e[1] *= k;
    e[2] *= k;
}

inline vec3 operator+(const vec3 &v1, const vec3 &v2)
{
    return vec3(v1.x() + v2.x(), v1.y() + v2.y(), v1.z() + v2.z());
}

inline vec3 operator-(const vec3 &v1, const vec3 &v2)
{
    return vec3(v1.x() - v2.x(), v1.y() - v2.y(), v1.z() - v2.z());
}

inline vec3 operator*(const vec3 &v1, const vec3 &v2)
{
    return vec3(v1.x() * v2.x(), v1.y() * v2.y(), v1.z() * v2.z());
}

inline vec3 operator/(const vec3 &v1, const vec3 &v2)
{
    return vec3(v1.x() / v2.x(), v1.y() / v2.y(), v1.z() / v2.z());
}

inline vec3 operator*(float t, const vec3 &v)
{
    return vec3(v.x() * t, v.y() * t, v.z() * t);
}

inline vec3 operator/(const vec3 v, float t)
{
    return vec3(v.x() / t, v.y() / t, v.z() / t);
}

inline vec3 operator*(const vec3 &v, float t)
{
    return vec3(v.x() * t, v.y() * t, v.z() * t);
}

inline float dot(const vec3 &v1, const vec3 &v2)
{
    return v1.x() * v2.x() + v1.y() * v2.y() + v1.z() * v2.z();
}

inline vec3 cross(const vec3 &v1, const vec3 &v2)
{
    return vec3(v1.y() * v2.z() - v1.z() * v2.y(),
                v1.z() * v2.x() - v1.x() * v2.z(),
                v1.x() * v2.y() - v1.y() * v2.x());
}

inline vec3 &vec3::operator+=(const vec3 &v)
{
    e[0] += v.x();
    e[1] += v.y();
    e[2] += v.z();
    return *this;
}

inline vec3 &vec3::operator*=(const vec3 &v)
{
    e[0] *= v.x();
    e[1] *= v.y();
    e[2] *= v.z();
    return *this;
}

inline vec3 &vec3::operator/=(const vec3 &v)
{
    e[0] /= v.x();
    e[1] /= v.y();
    e[2] /= v.z();
    return *this;
}

inline vec3 &vec3::operator-=(const vec3 &v)
{
    e[0] -= v.x();
    e[1] -= v.y();
    e[2] -= v.z();
    return *this;
}

inline vec3 &vec3::operator*=(const float t)
{
    e[0] *= t;
    e[1] *= t;
    e[2] *= t;
    return *this;
}

inline vec3 &vec3::operator/=(const float t)
{
    float k = 1.0f / t;

    e[0] *= k;
    e[1] *= k;
    e[2] *= k;
    return *this;
}

inline vec3 unit_vector(vec3 v)
{
    return v / v.length();
}