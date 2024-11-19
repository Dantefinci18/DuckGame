#include "enemigo.h"


Enemigo::Enemigo(int id,std::string color,float x, float y, SdlWindow& window) 
    : id(id), duck(window,x,y,color) {
}


int Enemigo::get_id() const {
    return id;
}

void Enemigo::mover_a(float nueva_x, float nueva_y) {
    duck.mover_a(nueva_x, nueva_y);
}

void Enemigo::renderizar() {
    duck.render();
}
 
void Enemigo::set_weapon(WeaponType new_weapon) {
    duck.set_weapon(new_weapon);
}

Enemigo::~Enemigo() {}