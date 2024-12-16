#include "PistolaCowboy.h"

// Constructor implementation
PistolaCowboy::PistolaCowboy() : Weapon(6, WeaponType::PistolaCowboy, 20 * TILES) {}

// reload implementation
void PistolaCowboy::reload() {
    ammo = 6;
}

// es_automatica implementation
bool PistolaCowboy::es_automatica() {
    return false;
}

// shoot implementation
std::vector<Vector> PistolaCowboy::shoot(Vector from, Vector direction, bool& tiene_retroceso) {
    std::vector<Vector> destinations;

    if (ammo <= 0) {
        return destinations;
    }

    ammo--;
    tiene_retroceso = false;

    // Normalize the direction vector to get a unit vector
    float magnitude = direction.magnitude();
    Vector unitDirection(direction.x / magnitude, direction.y / magnitude);

    // Calculate the endpoint by moving 'range' units along the direction
    Vector endpoint = from + unitDirection * range;

    destinations.push_back(endpoint);
    return destinations;
}

// Destructor implementation
PistolaCowboy::~PistolaCowboy() {}
