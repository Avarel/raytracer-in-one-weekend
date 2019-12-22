#include <math.h>

// Inline member functions need to live in the header file.

class vec3
{
public:
    vec3() {}
    vec3(float e0, float e1, float e2)
    {
        e[0] = e0;
        e[1] = e1;
        e[2] = e2;
    }

    inline float x() const { return e[0]; }
    inline float y() const { return e[1]; }
    inline float z() const { return e[2]; }
    inline float r() const { return x(); }
    inline float g() const { return y(); }
    inline float b() const { return z(); }

    inline const vec3 &operator+() const { return *this; }
    inline vec3 operator-() const { return vec3(-x(), -y(), -z()); }
    inline float operator[](int i) const { return e[i]; }
    inline float &operator[](int i) { return e[i]; }

    inline vec3 &operator+=(const vec3 &v2);
    inline vec3 &operator-=(const vec3 &v2);
    inline vec3 &operator*=(const vec3 &v2);
    inline vec3 &operator/=(const vec3 &v2);
    inline vec3 &operator*=(const float t);
    inline vec3 &operator/=(const float t);

    inline float length() const
    {
        return sqrt(x() * x() + y() * y() + z() * z());
    }
    inline float squared_length() const
    {
        return x() * x() + y() * y() + z() * z();
    }

    inline void make_unit_vector();

    float e[3];
};