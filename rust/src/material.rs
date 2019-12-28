use crate::vec3::Vec3;
use rand::Rng;

#[non_exhaustive]
pub enum Material {
    Dielectric(f64)
}

pub fn random_in_unit_sphere() -> Vec3<f64> {
    let mut position: Vec3<f64>;

    position = Vec3::from(rand::random(), rand::random(), rand::random()) * 2.0;
    while position.squared_length() >= 1.0 {
        position = Vec3::from(rand::random(), rand::random(), rand::random()) * 2.0;
    }

    position
}

