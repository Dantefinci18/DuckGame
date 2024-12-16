#include "Escopeta.h"

// Constructor implementation
Escopeta::Escopeta() 
    : Weapon(2, WeaponType::Escopeta, 9 * TILES), cargada(false), dispersion(3.0f) {}

// reload implementation
void Escopeta::reload() {
    ammo = 2;
}

// es_automatica implementation
bool Escopeta::es_automatica() {
    return false;
}

// shoot implementation
std::vector<Vector> Escopeta::shoot(Vector from, Vector direction, bool& tiene_retroceso) {
    std::vector<Vector> destinations;

    if (!cargada) {
        if (ammo > 0) {
            ammo--;
            cargada = true;
        }
        return destinations;
    }

    cargada = false;
    tiene_retroceso = false;

    for (int i = 0; i < 6; i++) {
        float dispersion_value = get_random_dispersion();
        Vector orthogonalDirection = direction;

        if (direction.x == 0 && direction.y == 1) { 
            orthogonalDirection = Vector(dispersion_value, 0);
        } else {
            orthogonalDirection = Vector(0, dispersion_value);
        }

        float magnitude = direction.magnitude();
        Vector unitDirection(direction.x / magnitude, direction.y / magnitude);

        Vector endpoint = from + unitDirection * range + orthogonalDirection;
        destinations.push_back(endpoint);
    }

    return destinations;
}

// Destructor implementation
Escopeta::~Escopeta() {}

// get_random_dispersion implementation
float Escopeta::get_random_dispersion() {
    static std::random_device rd;
    static std::mt19937 generator(rd());
    static std::uniform_real_distribution<float> distribution(-dispersion, dispersion);
    return distribution(generator);
}
