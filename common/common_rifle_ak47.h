#ifndef COMMON_RIFLE_AK47_H
#define COMMON_RIFLE_AK47_H

#include "common_weapon.h"
#include <chrono>
#include <random>
#include <vector>
#include <iostream>

class RifleAK47 : public Weapon {
public:
    RifleAK47()
        : Weapon(30, WeaponType::RifleAK47, 13 * TILES),
          retroceso(true),
          dispersion(6.0f),
          last_shot_time(std::chrono::steady_clock::now()),
          shoot_interval(100) {}

    void reload() override {
        ammo = 30;
    }

    bool es_automatica() override {
        return true;
    }

    std::vector<Vector> shoot(Vector from, Vector direction, bool& tiene_retroceso) override {
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

    virtual ~RifleAK47() {}

private:
    bool retroceso;
    float dispersion;
    std::chrono::steady_clock::time_point last_shot_time;
    const std::chrono::milliseconds shoot_interval;

    float get_random_dispersion() {
        static std::random_device rd;
        static std::mt19937 generator(rd());
        static std::uniform_real_distribution<float> distribution(-dispersion, dispersion);
        return distribution(generator);
    }

    bool puede_disparar() {
        auto now = std::chrono::steady_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - last_shot_time);
        return elapsed >= shoot_interval;
    }
};

#endif // COMMON_RIFLE_AK47_H
