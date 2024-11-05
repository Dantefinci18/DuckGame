#define ANCHO_IMG_DUCK_TOTAL 192
#define DESPLAZAMIENTO 3
#define ANCHO_IMG_SALTO_TOTAL 

#include "DuckAnimacion.h"

#include <SDL2/SDL_render.h>

DuckAnimacion::DuckAnimacion(SdlWindow& window, float x_inicial, float y_inicial):
        movimientos_en_x("../Imagenes/DuckMovimientos.png", window),
        movimiento_en_y("../Imagenes/DuckSalto.png", window),
        x_actual(x_inicial),
        y_actual(y_inicial) {}

void DuckAnimacion::render() {
    //if(y_actual < y_des){

    /*}else*/ if (x_actual < x_des) {
        x_actual += DESPLAZAMIENTO;
        flip = SDL_FLIP_NONE;

        if (x_img < ANCHO_IMG_DUCK_TOTAL) {
            x_img += ANCHO_IMG_DUCK;

        } else {
            x_img = ANCHO_IMG_DUCK;
        }

    } else if (x_actual > x_des) {
        x_actual -= DESPLAZAMIENTO;
        flip = SDL_FLIP_HORIZONTAL;

        if (x_img < ANCHO_IMG_DUCK_TOTAL) {
            x_img += ANCHO_IMG_DUCK;

        } else {
            x_img = ANCHO_IMG_DUCK;
        }

    } else {
        x_img = 0;
        quieto = true;
    }

    Area srcArea(x_img, 0, ANCHO_IMG_DUCK, ALTO_IMG_DUCK);
    Area destArea(x_actual, y_actual, ANCHO_IMG_DUCK, ALTO_IMG_DUCK);

    movimientos_en_x.render(srcArea, destArea, flip);
}

bool DuckAnimacion::esta_quieto() { return quieto; }

void DuckAnimacion::mover_a_una_posicion(float x, float y) {
    if (x != x_des) {
        quieto = false;
    }

    x_des = x;
    y_des = y;
}
