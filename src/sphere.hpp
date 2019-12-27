#ifndef SPHERE_HPP
#define SPHERE_HPP
#include "hitable.hpp"
#include "ray.hpp"

class sphere : public hitable {
public:
    vec3 center;
    float radius;
    material *mat_ptr;

    sphere() {}
    sphere(vec3 cen, float r, material *mat) : center(cen), radius(r), mat_ptr(mat) {}
    virtual bool hit(const ray &r, float t_min, float t_max, hit_record &rec) const;
};

bool sphere::hit(const ray &r, float t_min, float t_max, hit_record &rec) const {
    // Return t=parameter where the ray hits the sphere.
    vec3 oc = r.origin() - center;
    // Running the quadratic formula on the ray/sphere intersection equation.
    float a = dot(r.direction(), r.direction());
    float b = dot(oc, r.direction());
    float c = dot(oc, oc) - radius * radius;
    float discriminant = b * b - a * c;
    if (discriminant > 0) {
        float temp = (-b - sqrt(discriminant)) / a;
        if (temp < t_max && temp > t_min) {
            rec.t = temp;
            rec.p = r.point_at_parameter(temp);
            rec.normal = (rec.p - center) / radius;
            rec.mat_ptr = mat_ptr;
            return true;
        }
        temp = (-b + sqrt(discriminant)) / a;
        if (temp < t_max && temp > t_min) {
            rec.t = temp;
            rec.p = r.point_at_parameter(rec.t);
            rec.normal = (rec.p - center) / radius;
            rec.mat_ptr = mat_ptr;
            return true;
        }
    }
    return false;
}

#endif