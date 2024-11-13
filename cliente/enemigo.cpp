#include "enemigo.h"


Enemigo::Enemigo(int id, float x, float y, SdlWindow& window, std::vector<Collidable*> collidables) 
    : id(id), duckAnimacion(window, x, y, collidables) {
}


int Enemigo::get_id() const {
    return id;
}

void Enemigo::mover_a(float nueva_x, float nueva_y) {
    duckAnimacion.mover_a_una_posicion(nueva_x, nueva_y);
}

void Enemigo::renderizar() {
    duckAnimacion.render();
}
 
Enemigo::~Enemigo() {}