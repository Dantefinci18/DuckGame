#ifndef COMMON_ESCOPETA_H
#define COMMON_ESCOPETA_H

#include "common_weapon.h"
#include <random>
#include <vector>

class Escopeta : public Weapon {
public:
    Escopeta() 
    : Weapon(2, WeaponType::Escopeta, 9 * TILES), cargada(false), dispersion(3.0f) {}

    void reload() override {
        ammo = 2;
    }

    bool es_automatica() override {
        return false;
    }

    std::vector<Vector> shoot(Vector from, Vector direction, bool& tiene_retroceso) override {
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

    virtual ~Escopeta() {}

private:
    bool cargada;
    float dispersion;

    float get_random_dispersion() {
        static std::random_device rd;
        static std::mt19937 generator(rd());
        static std::uniform_real_distribution<float> distribution(-dispersion, dispersion);
        return distribution(generator);
    }
};

#endif // COMMON_ESCOPETA_H
