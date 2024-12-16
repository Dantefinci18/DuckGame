#ifndef COMMON_RIFLE_AK47_H
#define COMMON_RIFLE_AK47_H

#include "Weapon.h"
#include <chrono>
#include <vector>

class RifleAK47 : public Weapon {
public:
    RifleAK47();

    void reload() override;
    bool es_automatica() override;
    std::vector<Vector> shoot(Vector from, Vector direction, bool& tiene_retroceso) override;

    virtual ~RifleAK47();

private:
    bool retroceso;
    float dispersion;
    std::chrono::steady_clock::time_point last_shot_time;
    const std::chrono::milliseconds shoot_interval;

    float get_random_dispersion();
    bool puede_disparar();
};

#endif // COMMON_RIFLE_AK47_H
