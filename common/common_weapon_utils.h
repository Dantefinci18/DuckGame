#include "common_weapon.h"
#include <memory>
#include "common_pistola_cowboy.h"
class WeaponUtils {
public:
    static std::unique_ptr<Weapon> create_weapon(WeaponType type) {
        switch (type) {
            case WeaponType::PistolaCowboy:
                return std::make_unique<PistolaCowboy>();
            default:
                throw std::invalid_argument("Unknown weapon type");
        }
    }
};