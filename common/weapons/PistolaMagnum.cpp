#include "PistolaMagnum.h"
#include <random>
#include <iostream>

PistolaMagnum::PistolaMagnum()
    : Weapon(6, WeaponType::PistolaMagnum, 20 * TILES),
      retroceso(true),
      dispersion(4.0f) {}

void PistolaMagnum::reload() {
    ammo = 6;
}

bool PistolaMagnum::es_automatica() {
    return false;
}

std::vector<Vector> PistolaMagnum::shoot(Vector from, Vector direction, bool& tiene_retroceso) {
    std::vector<Vector> destinations;

    if (ammo <= 0) {
        return destinations;
    }

    ammo--;
    tiene_retroceso = retroceso;

    float dispersion_value = get_random_dispersion();
    Vector orthogonalDirection = direction;
    
    if (direction.x == 0 && direction.y == 1) {
        orthogonalDirection = Vector(dispersion_value, 0); // Dispersión en x
    } else {
        orthogonalDirection = Vector(0, dispersion_value); // Dispersión en y
    }

    float magnitude = direction.magnitude();
    Vector unitDirection(direction.x / magnitude, direction.y / magnitude);

    Vector endpoint = from + unitDirection * range + orthogonalDirection;
    destinations.push_back(endpoint);

    return destinations;
}

PistolaMagnum::~PistolaMagnum() {}

float PistolaMagnum::get_random_dispersion() {
    static std::random_device rd; 
    static std::mt19937 generator(rd());
    static std::uniform_real_distribution<float> distribution(-dispersion, dispersion); // dispersión
    return distribution(generator);
}
