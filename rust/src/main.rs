mod hittable;
mod sphere;
mod vec3;
mod material;
mod ray;
mod camera;

use vec3::{Vec3, vec3};
use hittable::Hittable;
use ray::Ray;
use material::Material;
use camera::Camera;

use rayon::prelude::*;

use std::io::{self, Write};

fn main() -> io::Result<()> {
    let mat_1 = Material::lambertian(vec3(0.1, 0.2, 0.5));
    let mat_2 = Material::lambertian(vec3(0.8, 0.8, 0.0));
    let mat_3 = Material::metal(vec3(0.8, 0.6, 0.2), 0.3);
    let mat_4 = Material::dielectric(1.5);
    let world = Hittable::list(vec![
        Hittable::sphere(vec3(0.0, 0.0, -1.0), 0.5, &mat_1),
        Hittable::sphere(vec3(0.0, -100.5, -1.0), 100.0, &mat_2),
        Hittable::sphere(vec3(1.0, 0.0, -1.0), 0.5, &mat_3),
        Hittable::sphere(vec3(-1.0, 0.0, -1.0), 0.5, &mat_4),
        Hittable::sphere(vec3(-1.0, 0.0, -1.0), -0.45, &mat_4),
    ]);

    let nx = 800;
    let ny = 400;
    let ns = 500;

    let mut file = std::fs::OpenOptions::new().write(true).create(true).open("./output/default.ppm")?;
    file.set_len(0)?;
    write!(file, "P3\n{} {}\n255\n", nx, ny)?;

    let look_from = vec3(3.0, 3.0, 2.0);
    let look_at = vec3(0.0, 0.0, -1.0);
    let dist_to_focus = (look_from - look_at).length();
    let aperture = 2.0;
    let camera = Camera::new(look_from, look_at, vec3(0.0, 1.0, 0.0), 20.0, f64::from(nx) / f64::from(ny), aperture, dist_to_focus);

    for j in (0..ny).rev() {
        for i in 0..nx {
            // Perform the anti-aliasing step with parallelism made easy.
            let mut col = (0..ns).into_par_iter().map(|_| {
                let u = (f64::from(i) + rand::random::<f64>()) / f64::from(nx);
                let v = (f64::from(j) + rand::random::<f64>()) / f64::from(ny);
                let ray = camera.get_ray(u, v);
                color(ray, &world, 0)
            }).reduce(|| Vec3::default(), |a, b| a + b);

            col /= f64::from(ns);
            col = col.sqrt();
            col *= 255.99;
            col = col.round();

            write!(file, "{} {} {}\n", col.x, col.y, col.z)?;
        }
    }

    Ok(())
}

fn color(ray: Ray<f64>, world: &Hittable, depth: usize) -> Vec3<f64> {
    if let Some(rec) = world.hit(&ray, 0.00001, std::f64::MAX) {
        if depth >= 50 {
            return Vec3::default()
        } else if let Some((scattered, attenuation)) = rec.material.scatter(ray, rec) {
            return attenuation * color(scattered, world, depth + 1)
        } else {
            return Vec3::default()
        }
    }

    let unit_direction = ray.direction.unit();
    let t = 0.5 * (unit_direction.y + 1.0);
    (1.0 - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0)
}