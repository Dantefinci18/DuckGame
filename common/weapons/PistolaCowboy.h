#ifndef COMMON_PISTOLA_COWBOY_H
#define COMMON_PISTOLA_COWBOY_H

#include "Weapon.h"
#include <vector>

class PistolaCowboy : public Weapon {
public:
    PistolaCowboy();

    void reload() override;
    bool es_automatica() override;
    std::vector<Vector> shoot(Vector from, Vector direction, bool& tiene_retroceso) override;

    virtual ~PistolaCowboy();
};

#endif // COMMON_PISTOLA_COWBOY_H
