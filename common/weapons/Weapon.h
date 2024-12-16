#ifndef COMMON_WEAPON_H
#define COMMON_WEAPON_H

#include "../../server/Vector.h"
#include <vector>
#include <cmath>
#include <iostream>

// Listar las armas como aparecen de izquierda a derecha en la imagen guns
enum class WeaponType {
    PistolaCowboy,
    PistolaMagnum,
    PistolaDuelos,
    RifleAK47,
    Escopeta,
    None
    // Future types can be added here
};

class Weapon {
public:
    static constexpr int TILES = 12;
    int ammo;
    WeaponType type;
    int range;

    // Constructor
    Weapon(int ammo, WeaponType type, int range);

    // Destructor
    virtual ~Weapon();

    // Getters
    WeaponType get_type();

    // Pure virtual functions
    virtual std::vector<Vector> shoot(Vector from, Vector direction, bool& tiene_retroceso) = 0;
    virtual void reload() = 0;
    virtual bool es_automatica() = 0;
};

#endif
