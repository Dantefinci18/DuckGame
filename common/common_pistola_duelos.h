#ifndef COMMON_PISTOLA_DUELOS_H
#define COMMON_PISTOLA_DUELOS_H

#include "common_weapon.h"
#include <chrono>
#include <random>
#include <vector>
#include <iostream>
class PistolaDuelos : public Weapon {
public:
    PistolaDuelos()
        : Weapon(1, WeaponType::PistolaDuelos, 5 * TILES),
          retroceso(false),
          dispersion(7.0f) {}

    void reload() override {
        ammo = 1;
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
        tiene_retroceso = retroceso;

        float dispersion_value = get_random_dispersion();

        Vector orthogonalDirection = direction;
        if (direction.x == 0 && direction.y == 1) { 
            std::cout << "tira para arriba, dispersion en x" << std::endl;
            orthogonalDirection = Vector(dispersion_value, 0);
        } else {
            std::cout << "tira para los costados, dispersion en y" << std::endl;
            orthogonalDirection = Vector(0, dispersion_value);
        }

        float magnitude = direction.magnitude();
        Vector unitDirection(direction.x / magnitude, direction.y / magnitude);

        Vector endpoint = from + unitDirection * range + orthogonalDirection;
        destinations.push_back(endpoint);

        return destinations;
    }

    virtual ~PistolaDuelos() {}

private:
    bool retroceso;
    float dispersion;

    float get_random_dispersion() {
        static std::random_device rd;
        static std::mt19937 generator(rd());
        static std::uniform_real_distribution<float> distribution(-dispersion, dispersion);
        return distribution(generator);
    }
};

#endif // COMMON_PISTOLA_DUELOS_H
