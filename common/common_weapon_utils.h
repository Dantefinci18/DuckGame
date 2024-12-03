#ifndef COMMON_WEAPON_UTILS_H
#define COMMON_WEAPON_UTILS_H

#include "common_weapon.h"
#include <memory>
#include "common_pistola_cowboy.h"
#include "common_pistola_magnum.h"
#include "common_pistola_duelos.h"
#include "common_rifle_ak47.h"
#include "common_escopeta.h"
#include "common_sniper.h"
#include "common_pewpew_laser.h"
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
            case WeaponType::Sniper:
                return std::make_unique<Sniper>();
            case WeaponType::PewPewLaser:
                return std::make_unique<PewPewLaser>();
            default:
                throw std::invalid_argument("Unknown weapon type");
        }
    }
};

#endif // COMMON_WEAPON_UTILS_H