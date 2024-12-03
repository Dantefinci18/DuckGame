#ifndef COMMON_PISTOLA_COWBOY_H
#define COMMON_PISTOLA_COWBOY_H
#include "common_weapon.h"
class PistolaCowboy : public Weapon {
    public:
    PistolaCowboy() : Weapon(6, WeaponType::PistolaCowboy, 20 * TILES) {}

    void reload() override {
        ammo = 6;
    }
    bool es_automatica() override {
        return false;
    }

    std::vector<Vector> shoot(Vector from, Vector direction, bool& tiene_retroceso) override{
        std::vector<Vector> destinations;

        if(ammo <= 0){
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
    virtual ~PistolaCowboy() {}
};
#endif