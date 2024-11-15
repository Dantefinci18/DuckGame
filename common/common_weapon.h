#ifndef COMMON_WEAPON_H
#define COMMON_WEAPON_H
#include "../server/Vector.h"
#include <vector>
#include <cmath>
enum class WeaponType {
    PistolaCowboy
    // Future types can be added here
};

class Weapon {    
    public:
    int ammo;
    WeaponType type;
    int range;
    WeaponType get_type() {
        return type;
    }
    
    Weapon(int ammo, WeaponType type, int range) : ammo(ammo), type(type), range(range) {}
    // Devuelve una lista de puntos a donde tiene que ir la bala.
    virtual std::vector<Vector> shoot(Vector from, Vector direction);
    virtual void reload();
};
#endif