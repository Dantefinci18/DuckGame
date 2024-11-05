#define ANCHO_IMG_DUCK_TOTAL 400
#define DESPLAZAMIENTO 3
#define TIEMPO_EN_DEPLAZARSE 150

#include "DuckAnimacion.h"

#include <SDL2/SDL_render.h>

DuckAnimacion::DuckAnimacion(SdlWindow& window, float x_inicial, float y_inicial):
        movimientos("../Imagenes/DuckMovimientos.png", window),
        x_actual(x_inicial),
        y_actual(y_inicial) {}

void DuckAnimacion::render() {
    if (x_actual < x_des) {
        x_actual += DESPLAZAMIENTO;
        flip = SDL_FLIP_NONE;

        if (x_img < ANCHO_IMG_DUCK_TOTAL) {
            x_img += ANCHO_IMG_DUCK;

        } else {
            x_img = 0;
        }

    } else if (x_actual > x_des) {
        x_actual -= DESPLAZAMIENTO;
        flip = SDL_FLIP_HORIZONTAL;

        if (x_img < ANCHO_IMG_DUCK_TOTAL) {
            x_img += ANCHO_IMG_DUCK;

        } else {
            x_img = 0;
        }

    } else {
        x_img = 0;
        quieto = true;
    }

    Area srcArea(x_img, 0, ANCHO_IMG_DUCK, ALTO_IMG_DUCK);
    Area destArea(x_actual, y_actual, ANCHO_IMG_DUCK, ALTO_IMG_DUCK);

    movimientos.render(srcArea, destArea, flip);
}

bool DuckAnimacion::esta_quieto() { return quieto; }

void DuckAnimacion::mover_a_una_posicion(float x, float y) {
    if (x != x_des) {
        quieto = false;
    }

    x_des = x;
    y_des = y;
}
