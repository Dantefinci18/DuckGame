#ifndef COMMON_PISTOLA_COWBOY_H
#define COMMON_PISTOLA_COWBOY_H
#include "common_weapon.h"
class PistolaCowboy : public Weapon {
    public:
    PistolaCowboy() : Weapon(6, WeaponType::PistolaCowboy, 60) {}

    void reload() override {
        ammo = 6;
        std::cout << "Municion: " << ammo << std::endl;
    }

    std::vector<Vector> shoot(Vector from, Vector direction, bool is_shooting) override{
        
        std::vector<Vector> destinations;

        if(ammo <= 0){
            return destinations;
        }

        ammo--;

        // Normalize the direction vector to get a unit vector
        float magnitude = direction.magnitude();//std::sqrt(direction.x * direction.x + direction.y * direction.y);
        Vector unitDirection(direction.x / magnitude, direction.y / magnitude);

        // Calculate the endpoint by moving 'range' units along the direction
        Vector endpoint = from + unitDirection * range;

        destinations.push_back(endpoint);
        return destinations;
    }
    virtual ~PistolaCowboy() {}
};
#endif