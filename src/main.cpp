#include "camera.hpp"
#include "hitable_list.hpp"
#include "material.hpp"
#include "ray.hpp"
#include "sphere.hpp"
#include <cfloat>
#include <iostream>

using std::cout;
using std::endl;

vec3 color(const ray& r, hitable* world, int depth)
{
    hit_record rec;
    if (world->hit(r, 0.00001, MAXFLOAT, rec))
    {
        ray scattered;
        vec3 attenuation;

        if (depth < 50 && rec.mat_ptr->scatter(r, rec, attenuation, scattered))
        {
            return attenuation * color(scattered, world, depth + 1);
        }
        else
        {
            return vec3(0, 0, 0);
        }
    }

    // Otherwise return the background.
    vec3 unit_direction = unit_vector(r.direction());
    float t = 0.5 * (unit_direction.y + 1);
    return (1 - t) * vec3(1, 1, 1) + t * vec3(0.5, 0.7, 1.0);
}

int main()
{
    int nx = 200; // x size
    int ny = 100; // y size
    int ns = 100; // samples
    cout << "P3" << endl
         << nx << " " << ny << endl
         << "255" << endl;

    vec3 lower_left_corner(-2, -1, -1);
    vec3 horizontal(4, 0, 0);
    vec3 vertical(0, 2, 0);
    vec3 origin(0, 0, 0);

    hitable* list[4];
    list[0] = new sphere(vec3(0, 0, -1), 0.5, new lambertian(vec3(0.8, 0.3, 0.3)));
    list[1] = new sphere(vec3(0, -100.5, -1), 100, new lambertian(vec3(0.8, 0.8, 0.0)));
    list[2] = new sphere(vec3(1, 0, -1), 0.5, new metal(vec3(0.8, 0.6, 0.2), 0.3));
    list[3] = new sphere(vec3(-1, 0, -1), 0.5, new metal(vec3(0.8, 0.8, 0.8), 1));
    hitable* world = new hitable_list(list, 4);

    camera cam;

    for (int j = ny - 1; j >= 0; j--)
    {
        for (int i = 0; i < nx; i++)
        {
            vec3 col(0, 0, 0);
            for (int s = 0; s < ns; s++)
            {
                float u = float(i + drand48()) / float(nx);
                float v = float(j + drand48()) / float(ny);
                ray r = cam.get_ray(u, v);
                col += color(r, world, 0);
            }

            col /= float(ns);
            col = sqrt_vec3(col);
            col *= 255.99;
            col = round_int(col);

            cout << col << endl;
        }
    }
    return 0;
}