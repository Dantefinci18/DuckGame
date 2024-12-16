#ifndef COMMON_ESCOPETA_H
#define COMMON_ESCOPETA_H

#include "Weapon.h"
#include <random>
#include <vector>

class Escopeta : public Weapon {
public:
    Escopeta();

    void reload() override;
    bool es_automatica() override;
    std::vector<Vector> shoot(Vector from, Vector direction, bool& tiene_retroceso) override;

    virtual ~Escopeta();

private:
    bool cargada;
    float dispersion;

    float get_random_dispersion();
};

#endif // COMMON_ESCOPETA_H
