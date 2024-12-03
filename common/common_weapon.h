#ifndef COMMON_WEAPON_H
#define COMMON_WEAPON_H
#include "../server/Vector.h"
#include <vector>
#include <cmath>

// Listar las armas como aparecen de izquierda a derecha en la imagen guns
enum class WeaponType {
    PistolaCowboy,
    PistolaMagnum,
    PistolaDuelos,
    RifleAK47,
    Escopeta,
    Sniper,
    PewPewLaser,
    None
    // Future types can be added here
};

class Weapon {    
    public:
    static constexpr int TILES = 12;
    int ammo;
    WeaponType type;
    int range;

    WeaponType get_type() {
        return type;
    }

    virtual ~Weapon() {}; 
    Weapon(int ammo, WeaponType type, int range) : ammo(ammo), type(type), range(range) {}

    // Devuelve una lista de puntos a donde tiene que ir la bala.
    virtual std::vector<Vector> shoot(Vector from, Vector direction, bool& tiene_retroceso) = 0;
    virtual void reload() = 0;
    virtual bool es_automatica() = 0;
};
#endif
