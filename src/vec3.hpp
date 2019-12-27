#ifndef VEC3_HPP
#define VEC3_HPP

#include <iostream>
#include <math.h>
#include <stdlib.h>

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

    inline const vec3& operator+() const { return *this; }
    inline vec3 operator-() const { return vec3(-x, -y, -z); }

    // inline float operator[](int i) const { return e[i]; }
    // inline float &operator[](int i) { return e[i]; }

    inline vec3& operator+=(const vec3& v2);
    inline vec3& operator-=(const vec3& v2);
    inline vec3& operator*=(const vec3& v2);
    inline vec3& operator/=(const vec3& v2);
    inline vec3& operator*=(const float t);
    inline vec3& operator/=(const float t);

    inline float length() const;
    inline float squared_length() const;

    // inline void make_round_int();
    // inline void make_unit_vector();
};

inline std::istream& operator>>(std::istream& is, vec3& t)
{
    is >> t.x >> t.y >> t.z;
    return is;
}

inline std::ostream& operator<<(std::ostream& os, const vec3& t)
{
    os << t.x << " " << t.y << " " << t.z;
    return os;
}

inline vec3 operator+(const vec3& v1, const vec3& v2)
{
    return vec3(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}

inline vec3 operator-(const vec3& v1, const vec3& v2)
{
    return vec3(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}

inline vec3 operator*(const vec3& v1, const vec3& v2)
{
    return vec3(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z);
}

inline vec3 operator/(const vec3& v1, const vec3& v2)
{
    return vec3(v1.x / v2.x, v1.y / v2.y, v1.z / v2.z);
}

inline vec3 operator*(float t, const vec3& v)
{
    return vec3(v.x * t, v.y * t, v.z * t);
}

inline vec3 operator/(const vec3 v, float t)
{
    return vec3(v.x / t, v.y / t, v.z / t);
}

inline vec3 operator*(const vec3& v, float t)
{
    return vec3(v.x * t, v.y * t, v.z * t);
}

inline float dot(const vec3& v1, const vec3& v2)
{
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

inline vec3 cross(const vec3& v1, const vec3& v2)
{
    return vec3(v1.y * v2.z - v1.z * v2.y,
                v1.z * v2.x - v1.x * v2.z,
                v1.x * v2.y - v1.y * v2.x);
}

inline vec3& vec3::operator+=(const vec3& v)
{
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
}

inline vec3& vec3::operator*=(const vec3& v)
{
    x *= v.x;
    y *= v.y;
    z *= v.z;
    return *this;
}

inline vec3& vec3::operator/=(const vec3& v)
{
    x /= v.x;
    y /= v.y;
    z /= v.z;
    return *this;
}

inline vec3& vec3::operator-=(const vec3& v)
{
    x -= v.x;
    y -= v.y;
    z -= v.z;
    return *this;
}

inline vec3& vec3::operator*=(const float t)
{
    x *= t;
    y *= t;
    z *= t;
    return *this;
}

inline vec3& vec3::operator/=(const float t)
{
    float k = 1.0f / t;

    x *= k;
    y *= k;
    z *= k;
    return *this;
}

inline float vec3::length() const
{
    return sqrt(squared_length());
}

inline float vec3::squared_length() const
{
    return x * x + y * y + z * z;
}

// inline void vec3::make_round_int()
// {
//     x = int(x);
//     y = int(y);
//     z = int(z);
// }

// inline void vec3::make_unit_vector()
// {
//     float k = 1.0 / length();
//     x *= k;
//     y *= k;
//     z *= k;
// }

inline vec3 sqrt_vec3(vec3 v)
{
    return vec3(sqrt(v.x), sqrt(v.y), sqrt(v.z));
}

inline vec3 round_int(vec3 v)
{
    return vec3(int(v.x), int(v.y), int(v.z));
}

inline vec3 unit_vector(vec3 v)
{
    return v / v.length();
}

#endif