#include "RifleAK47.h"
#include <iostream>
#include <random>

// Constructor implementation
RifleAK47::RifleAK47()
    : Weapon(30, WeaponType::RifleAK47, 13 * TILES),
      retroceso(true),
      dispersion(6.0f),
      last_shot_time(std::chrono::steady_clock::now()),
      shoot_interval(100) {}

// reload implementation
void RifleAK47::reload() {
    ammo = 30;
}

// es_automatica implementation
bool RifleAK47::es_automatica() {
    return true;
}

// shoot implementation
std::vector<Vector> RifleAK47::shoot(Vector from, Vector direction, bool& tiene_retroceso) {
    std::vector<Vector> destinations;

    if (ammo <= 0 || !puede_disparar()) {
        return destinations;
    }

    ammo--;
    tiene_retroceso = retroceso;

    float dispersion_value = get_random_dispersion();
    Vector orthogonalDirection = direction;
    if (direction.x == 0 && direction.y == 1) {
        std::cout << "tira para arriba, dispersion en x" << std::endl;
        orthogonalDirection = Vector(dispersion_value, 0); // Dispersión en x
    } else {
        std::cout << "tira para los costados, dispersion en y" << std::endl;
        orthogonalDirection = Vector(0, dispersion_value); // Dispersión en y
    }

    float magnitude = direction.magnitude();
    Vector unitDirection(direction.x / magnitude, direction.y / magnitude);

    Vector endpoint = from + unitDirection * range + orthogonalDirection;
    destinations.push_back(endpoint);
    last_shot_time = std::chrono::steady_clock::now();
    return destinations;
}

// Destructor implementation
RifleAK47::~RifleAK47() {}

// get_random_dispersion implementation
float RifleAK47::get_random_dispersion() {
    static std::random_device rd;
    static std::mt19937 generator(rd());
    static std::uniform_real_distribution<float> distribution(-dispersion, dispersion);
    return distribution(generator);
}

// puede_disparar implementation
bool RifleAK47::puede_disparar() {
    auto now = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - last_shot_time);
    return elapsed >= shoot_interval;
}
