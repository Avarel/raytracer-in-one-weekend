#include <iostream>
#include "vec3.hpp"
#include "ray.hpp"

using std::cout;
using std::endl;

vec3 color(const ray &r)
{
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

    for (int j = ny - 1; j >= 0; j--)
    {
        for (int i = 0; i < nx; i++)
        {
            float u = float(i) / float(nx);
            float v = float(j) / float(ny);
            ray r(origin, lower_left_corner + u * horizontal + v * vertical);
            vec3 col = color(r);
            col *= 255.99;
            col = round_int(col);
            cout << col << endl;
        }
    }
    return 0;
}