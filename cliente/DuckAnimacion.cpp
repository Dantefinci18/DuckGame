#define ANCHO_IMG_DUCK_TOTAL 192
#define DESPLAZAMIENTO 2
#define TIEMPO_EN_DEPLAZARSE 150

#include "DuckAnimacion.h"

#include <SDL2/SDL_render.h>

DuckAnimacion::DuckAnimacion(SdlWindow& window):
        window(window), movimientos("../Imagenes/DuckMovimientos.png", window) {}

void DuckAnimacion::run() {
    std::cout << "DuckAnimacion running" << std::endl;
    while (_keep_running) {
        if (moverse_a_derecha) {
            x_des += DESPLAZAMIENTO;

            if (x_img < ANCHO_IMG_DUCK_TOTAL) {
                x_img += ANCHO_IMG_DUCK;
                SDL_Delay(TIEMPO_EN_DEPLAZARSE);

            } else {
                x_img = 0;
            }
        }

        if(moverse_a_izquierda){
            x_des -= DESPLAZAMIENTO;

            if (x_img < ANCHO_IMG_DUCK_TOTAL) {
                x_img += ANCHO_IMG_DUCK;
                SDL_Delay(TIEMPO_EN_DEPLAZARSE);

            } else {
                x_img = 0;
            }
        }
    }
}

void DuckAnimacion::render() {
    Area srcArea(x_img, 0, ANCHO_IMG_DUCK, ALTO_IMG_DUCK);
    Area destArea(x_des, y_des, ANCHO_IMG_DUCK, ALTO_IMG_DUCK);
    
    movimientos.render(srcArea,destArea,flip);
}

void DuckAnimacion::mover_a_derecha() { 
    moverse_a_derecha = true; 
    flip = SDL_FLIP_NONE;
}

void DuckAnimacion::mover_a_izquierda() { 
    moverse_a_izquierda = true; 
    flip = SDL_FLIP_HORIZONTAL;
}

void DuckAnimacion::dejar_de_moverse_a_derecha() {
    moverse_a_derecha = false;
    x_img = 0;
}

void DuckAnimacion::dejar_de_moverse_a_izquierda() {
    moverse_a_izquierda = false;
    x_img = 0;
}

