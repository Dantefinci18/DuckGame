#include "enemigo.h"


Enemigo::Enemigo(int id, float x, float y, SdlWindow& window) 
    : id(id), duck(window, x, y,"_rojo") {
}


int Enemigo::get_id() const {
    return id;
}

void Enemigo::mover_a(float nueva_x, float nueva_y) {
    duck.mover_a_una_posicion(nueva_x, nueva_y);
}

void Enemigo::renderizar() {
    duck.render();
}
 
void Enemigo::set_weapon(WeaponType new_weapon) {
    duck.set_weapon(new_weapon);
}

Enemigo::~Enemigo() {}