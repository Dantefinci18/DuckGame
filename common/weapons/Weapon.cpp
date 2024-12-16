#include "Weapon.h"

// Constructor implementation
Weapon::Weapon(int ammo, WeaponType type, int range)
    : ammo(ammo), type(type), range(range) {}

// Destructor implementation
Weapon::~Weapon() {}

// Getter implementation
WeaponType Weapon::get_type() {
    return type;
}
