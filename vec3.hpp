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

    // We will be using vec3 to store positions.
    inline float x() const;
    inline float y() const;
    inline float z() const;

    // We will also be using vec3 to store colors.
    inline float r() const;
    inline float g() const;
    inline float b() const;

    inline const vec3 &operator+() const;
    inline vec3 operator-() const;
    inline float operator[](int i) const;
    inline float &operator[](int i);

    inline vec3 &operator+=(const vec3 &v2);
    inline vec3 &operator-=(const vec3 &v2);
    inline vec3 &operator*=(const vec3 &v2);
    inline vec3 &operator/=(const vec3 &v2);
    inline vec3 &operator*=(const float t);
    inline vec3 &operator/=(const float t);
    
    inline float length() const;
    inline float squared_length() const;
    inline void make_unit_vector();

    float e[3];
};