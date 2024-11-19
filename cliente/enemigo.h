#ifndef ENEMIGO_H
#define ENEMIGO_H

#include <string>
#include "duck.h"  
#include "Sdl/SdlWindow.h"
#include "../server/Collidable.h"
#include "../common/common_weapon.h"

class Enemigo {
public:
    Enemigo(int id,std::string,float x, float y, SdlWindow& window);

    int get_id() const;

    void mover_a(float nueva_x, float nueva_y);

    void renderizar();

    void set_weapon(WeaponType weapon);
    void kill();

    ~Enemigo();

private:
    int id;  
    Duck duck; 
};

#endif // ENEMIGO_H