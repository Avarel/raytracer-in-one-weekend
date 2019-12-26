#include <iostream>
#include <float.h>
#include "math.h"
#include "vec3.hpp"
#include "ray.hpp"
#include "hitable_list.hpp"
#include "sphere.hpp"

using std::cout;
using std::endl;

vec3 color(const ray &r, hitable *world)
{
    hit_record rec;
    if (world->hit(r, 0, MAXFLOAT, rec))
    {
        return 0.5 * vec3(rec.normal.x + 1, rec.normal.y + 1, rec.normal.z + 1);
    }

    // Otherwise return the background.
    vec3 unit_direction = unit_vector(r.direction());
    float t = 0.5 * (unit_direction.y + 1);
    return (1 - t) * vec3(1, 1, 1) + t * vec3(0.5, 0.7, 1.0);
}

int main()
{
    int nx = 200;
    int ny = 100;
    cout << "P3" << endl
         << nx << " " << ny << endl
         << "255" << endl;

    vec3 lower_left_corner(-2, -1, -1);
    vec3 horizontal(4, 0, 0);
    vec3 vertical(0, 2, 0);
    vec3 origin(0, 0, 0);

    hitable *list[2];
    list[0] = new sphere(vec3(0, 0, -1), 0.5);
    list[1] = new sphere(vec3(0, -100.5, -1), 100);
    hitable *world = new hitable_list(list, 2);

    for (int j = ny - 1; j >= 0; j--)
    {
        for (int i = 0; i < nx; i++)
        {
            float u = float(i) / float(nx);
            float v = float(j) / float(ny);

            ray r(origin, lower_left_corner + u * horizontal + v * vertical);
            vec3 col = color(r, world);
            col *= 255.99;
            col = round_int(col);

            cout << col << endl;
        }
    }
    return 0;
}