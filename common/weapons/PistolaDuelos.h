#ifndef COMMON_PISTOLA_DUELOS_H
#define COMMON_PISTOLA_DUELOS_H

#include "Weapon.h"
#include <vector>

class PistolaDuelos : public Weapon {
public:
    PistolaDuelos();

    void reload() override;
    bool es_automatica() override;
    std::vector<Vector> shoot(Vector from, Vector direction, bool& tiene_retroceso) override;

    virtual ~PistolaDuelos();

private:
    bool retroceso;
    float dispersion;

    float get_random_dispersion();
};

#endif // COMMON_PISTOLA_DUELOS_H
