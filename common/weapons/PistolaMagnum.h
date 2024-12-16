#ifndef COMMON_PISTOLA_MAGNUM_H
#define COMMON_PISTOLA_MAGNUM_H

#include "Weapon.h"
#include <vector>

class PistolaMagnum : public Weapon {
public:
    PistolaMagnum();

    void reload() override;
    bool es_automatica() override;
    std::vector<Vector> shoot(Vector from, Vector direction, bool& tiene_retroceso) override;

    virtual ~PistolaMagnum();

private:
    bool retroceso;
    float dispersion;

    float get_random_dispersion();
};

#endif // COMMON_PISTOLA_MAGNUM_H
