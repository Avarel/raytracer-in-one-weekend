#include "camera.hpp"
#include "hittable_list.hpp"
#include "material.hpp"
#include "ray.hpp"
#include "sphere.hpp"
#include <cfloat>
#include <iostream>

using std::cout;
using std::endl;

vec3 color(const ray &r, hittable *world, int depth) {
    hit_record rec;
    if (world->hit(r, 0.00001, MAXFLOAT, rec)) {
        ray scattered;
        vec3 attenuation;

        if (depth < 50 && rec.mat_ptr->scatter(r, rec, attenuation, scattered)) {
            return attenuation * color(scattered, world, depth + 1);
        } else {
            return vec3(0, 0, 0);
        }
    }

    // Otherwise return the background.
    vec3 unit_direction = unit_vector(r.direction());
    float t = 0.5 * (unit_direction.y + 1);
    return (1 - t) * vec3(1, 1, 1) + t * vec3(0.5, 0.7, 1.0);
}

hittable *random_scene() {
    int n = 500;
    hittable **list = new hittable*[n+1];
    list[0] =  new sphere(vec3(0,-1000,0), 1000, new lambertian(vec3(0.5, 0.5, 0.5)));
    int i = 1;
    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            float choose_mat = drand48();
            vec3 center(a+0.9*drand48(),0.2,b+0.9*drand48());
            if ((center-vec3(4,0.2,0)).length() > 0.9) {
                if (choose_mat < 0.8) {  // diffuse
                    list[i++] = new sphere(
                        center, 0.2,
                        new lambertian(vec3(drand48()*drand48(),
                                            drand48()*drand48(),
                                            drand48()*drand48()))
                    );
                }
                else if (choose_mat < 0.95) { // metal
                    list[i++] = new sphere(
                        center, 0.2,
                        new metal(vec3(0.5*(1 + drand48()),
                                       0.5*(1 + drand48()),
                                       0.5*(1 + drand48())),
                                  0.5*drand48())
                    );
                }
                else {  // glass
                    list[i++] = new sphere(center, 0.2, new dielectric(1.5));
                }
            }
        }
    }

    list[i++] = new sphere(vec3(0, 1, 0), 1.0, new dielectric(1.5));
    list[i++] = new sphere(vec3(-4, 1, 0), 1.0, new lambertian(vec3(0.4, 0.2, 0.1)));
    list[i++] = new sphere(vec3(4, 1, 0), 1.0, new metal(vec3(0.7, 0.6, 0.5), 0.0));

    return new hittable_list(list,i);
}

int main() {
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

    hittable *world = random_scene();

    vec3 lookfrom(13,2,3);
    vec3 lookat(0,0,0);
    float dist_to_focus = 10.0;
    float aperture = 0.1;

    camera cam(lookfrom, lookat, vec3(0,1,0), 20, float(nx)/float(ny), aperture, dist_to_focus);

    for (int j = ny - 1; j >= 0; j--) {
        for (int i = 0; i < nx; i++) {
            vec3 col(0, 0, 0);
            for (int s = 0; s < ns; s++) {
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