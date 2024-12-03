#ifndef COMMON_SNIPER_H
#define COMMON_SNIPER_H

#include "common_weapon.h"
#include <vector>

class Sniper : public Weapon {
public:
    Sniper() 
        : Weapon(3, WeaponType::Sniper, 30 * TILES) {}

    void reload() override {
        ammo = 3;
    }

    bool es_automatica() override {
        return false;
    }

    std::vector<Vector> shoot(Vector from, Vector direction, bool& tiene_retroceso) override {
        std::vector<Vector> destinations;

        if (ammo <= 0) {
            return destinations;
        }

        ammo--;

        tiene_retroceso = false;

        float magnitude = direction.magnitude();
        Vector unitDirection(direction.x / magnitude, direction.y / magnitude);

        Vector endpoint = from + unitDirection * range;
        destinations.push_back(endpoint);

        return destinations;
    }

    virtual ~Sniper() {}

private:
};

#endif // COMMON_SNIPER_H
