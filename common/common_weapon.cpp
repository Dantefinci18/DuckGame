#include "common_weapon.h"

class PistolaCowboy : public Weapon {
    PistolaCowboy() : Weapon(6, WeaponType::PistolaCowboy, 60) {}

    void reload() override {
        ammo = 6;
    }

    std::vector<Vector> shoot(Vector from, Vector direction) override{
        // Normalize the direction vector to get a unit vector
        std::vector<Vector> destinations;
        float magnitude = std::sqrt(direction.x * direction.x + direction.y * direction.y);
        Vector unitDirection(direction.x / magnitude, direction.y / magnitude);

        // Calculate the endpoint by moving 'range' units along the direction
        Vector endpoint = from + unitDirection * range;

        destinations.push_back(endpoint);
        return destinations;
    }
};