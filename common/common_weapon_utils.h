#ifndef COMMON_WEAPON_UTILS_H
#define COMMON_WEAPON_UTILS_H

#include "weapons/Weapon.h"
#include <memory>
#include "weapons/PistolaCowboy.h"
#include "weapons/PistolaMagnum.h"
#include "weapons/PistolaDuelos.h"
#include "weapons/RifleAK47.h"
#include "weapons/Escopeta.h"
class WeaponUtils {
public:
    static std::unique_ptr<Weapon> create_weapon(WeaponType type) {
        switch (type) {
            case WeaponType::PistolaCowboy:
                return std::make_unique<PistolaCowboy>();
            case WeaponType::PistolaMagnum:
                return std::make_unique<PistolaMagnum>();
            case WeaponType::RifleAK47:
                return std::make_unique<RifleAK47>();
            case WeaponType::PistolaDuelos:
                return std::make_unique<PistolaDuelos>();
            case WeaponType::Escopeta:
                return std::make_unique<Escopeta>();
            default:
                throw std::invalid_argument("Unknown weapon type");
        }
    }
};

#endif // COMMON_WEAPON_UTILS_H