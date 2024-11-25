#ifndef COMMON_PISTOLA_MAGNUM_H
#define COMMON_PISTOLA_MAGNUM_H

#include "common_weapon.h"
#include <cmath>
#include <random>
#include <vector>

class PistolaMagnum : public Weapon {
public:
    PistolaMagnum() : Weapon(6, WeaponType::PistolaMagnum, 200), retroceso(true), dispersion(4.0f) {}

    void reload() override {
        ammo = 6;
        std::cout << "Municion: " << ammo << std::endl;
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
        float dispersion = get_random_dispersion();
        
        Vector orthogonalDirection = direction;
        if (direction.x == 0 && direction.y == 1) { 
            std::cout << "tira para arriba, dispersion en x" << std::endl;
            orthogonalDirection = Vector(dispersion, 0); // Dispersión en x
        } else {
            std::cout << "tira para los costados, dispersion en y" << std::endl;
            orthogonalDirection = Vector(0, dispersion); // Dispersión en y
        }

        float magnitude = direction.magnitude();
        Vector unitDirection(direction.x / magnitude, direction.y / magnitude);

        Vector endpoint = from + unitDirection * range + orthogonalDirection;
        destinations.push_back(endpoint);

        return destinations;
    }

    virtual ~PistolaMagnum() {}

private:
    bool retroceso;
    float dispersion;
    float get_random_dispersion() {
        static std::random_device rd; 
        static std::mt19937 generator(rd());
        static std::uniform_real_distribution<float> distribution(-dispersion, dispersion); // dispersión
        return distribution(generator);
    }
};

#endif
