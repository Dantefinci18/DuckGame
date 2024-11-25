#include "enemigo.h"


Enemigo::Enemigo(int id,std::string color,float x, float y, SdlWindow& window) 
    : id(id), duck(window,x,y,color) {
}


int Enemigo::get_id() const {
    return id;
}

void Enemigo::mover_a(float nueva_x, float nueva_y, bool is_flapping, bool reset) {
    duck.mover_a(nueva_x, nueva_y, is_flapping, reset);
}

void Enemigo::renderizar() {
    //std::cout << "render_enemigo" << std::endl;
    duck.render();
}
 
void Enemigo::set_weapon(WeaponType new_weapon) {
    duck.set_weapon(new_weapon);
}

void Enemigo::kill() {
    duck.kill();
}

void Enemigo::agacharse() {
    duck.agacharse();
}

void Enemigo::levantarse() {
    duck.levantarse();
}
Enemigo::~Enemigo() {}