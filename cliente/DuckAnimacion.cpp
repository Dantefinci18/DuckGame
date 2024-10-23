#define ANCHO_IMG_DUCK_TOTAL 192
#define DESPLAZAMIENTO 2
#define TIEMPO_EN_DEPLAZARSE 150

#include "DuckAnimacion.h"

#include <SDL2/SDL.h>

DuckAnimacion::DuckAnimacion(SdlWindow& window):
        window(window), movimientos("../Imagenes/DuckMovimientos.png", window) {}

void DuckAnimacion::run() {
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
    }
}

void DuckAnimacion::render() {
    Area srcArea(x_img, 0, ANCHO_IMG_DUCK, ALTO_IMG_DUCK);
    Area destArea(x_des, y_des, ANCHO_IMG_DUCK, ALTO_IMG_DUCK);
    movimientos.render(srcArea, destArea);
}

void DuckAnimacion::mover_a_derecha() { moverse_a_derecha = true; }

void DuckAnimacion::quieto() {
    moverse_a_derecha = false;
    x_img = 0;
}
