#include "common_weapon.h"
#include <memory>
#include "common_pistola_cowboy.h"
#include "common_pistola_magnum.h"
#include "common_pistola_duelos.h"
#include "common_rifle_ak47.h"
class WeaponUtils {
public:
    static std::unique_ptr<Weapon> create_weapon(WeaponType type) {
        switch (type) {
            case WeaponType::PistolaCowboy:
                std::cout << "\033[31mSPAWNEO cowboy\033[0m" << std::endl;
                return std::make_unique<PistolaCowboy>();
            case WeaponType::PistolaMagnum:
                std::cout << "\033[31mSPAWNEO magnum\033[0m" << std::endl;
                return std::make_unique<PistolaMagnum>();
            case WeaponType::RifleAK47:
                std::cout << "\033[31mSPAWNEO AK47\033[0m" << std::endl;
                return std::make_unique<RifleAK47>();
            case WeaponType::PistolaDuelos:
                std::cout << "\033[31mSPAWNEO duelos\033[0m" << std::endl;
                return std::make_unique<PistolaDuelos>();
            default:
                throw std::invalid_argument("Unknown weapon type");
        }
    }
};