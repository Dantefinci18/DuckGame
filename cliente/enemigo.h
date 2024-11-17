#ifndef ENEMIGO_H
#define ENEMIGO_H

#include <string>
#include "DuckAnimacion.h"  
#include "Sdl/SdlWindow.h"
#include "../server/Collidable.h"
#include "../common/common_weapon.h"

class Enemigo {
public:
    Enemigo(int id, float x, float y, SdlWindow& window, std::vector<Collidable*> collidables);

    int get_id() const;

    void mover_a(float nueva_x, float nueva_y);

    void renderizar();

    void set_weapon(WeaponType weapon);

    ~Enemigo();

private:
    int id;  
    DuckAnimacion duckAnimacion;  
};

#endif // ENEMIGO_H