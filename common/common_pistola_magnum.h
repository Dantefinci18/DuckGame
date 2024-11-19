#ifndef COMMON_MAGNUM_H
#define COMMON_MAGNUM_H

#include "common_weapon.h"
#include <random>

class Magnum : public Weapon {
private:
    std::default_random_engine generator;
    std::uniform_real_distribution<float> dispersion_range;

public:
    Magnum() 
        : Weapon(6, WeaponType::Magnum, 20), dispersion_range(-0.1f, 0.1f) {}

    void reload() override {
        ammo = 6;
        std::cout << "Munición recargada: " << ammo << std::endl;
    }

    std::vector<Vector> shoot(const Vector& from, const Vector& direction, bool is_shooting) override {
        std::vector<Vector> destinations;

        if (ammo <= 0) {
            return destinations;
        }

        ammo--;

        // Normaliza el vector de dirección
        float magnitude = direction.magnitude();
        Vector unitDirection(direction.x / magnitude, direction.y / magnitude);

        // Aplica dispersión
        float dispersion_y = dispersion_range(generator);

        Vector dispersedDirection(unitDirection.x, unitDirection.y + dispersion_y);
        float dispersedMagnitude = dispersedDirection.magnitude();
        dispersedDirection = Vector(dispersedDirection.x / dispersedMagnitude, dispersedDirection.y / dispersedMagnitude);

        // Calcula el punto de impacto
        Vector endpoint = from + dispersedDirection * range;
        destinations.push_back(endpoint);

        //Acá falta el tema del retroceso, no se si aca especificamente o no pero falta

        return destinations;
    }

    virtual ~Magnum() {}
};

#endif
