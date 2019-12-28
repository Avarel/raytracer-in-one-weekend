mod hittable;
mod sphere;
mod vec3;
mod material;
mod ray;

use vec3::Vec3;

fn main() {
    let z = Vec3::from(1.0, 2.0, 3.0);

    let c = z * z;

    let hittable_list = hittable::Hittable::HittableList(vec![
        hittable::Hittable::Sphere(sphere::Sphere::new(Vec3::new(), 1.0, &material::Material::Dielectric(2.0))),
        hittable::Hittable::Sphere(sphere::Sphere::new(Vec3::new(), 1.0, &material::Material::Dielectric(2.0)))
    ]);

    println!("Hello, world! {:?} {}", c, rand::random::<f64>());
}
