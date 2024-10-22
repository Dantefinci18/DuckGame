#define ANCHO_IMG_DUCK_TOTAL 192

#include "DuckAnimacion.h"

#include <SDL2/SDL.h>

DuckAnimacion::DuckAnimacion(SdlWindow& window):
        window(window),
        movimientos("/home/dante/Taller/DuckGame/Imagenes/DuckMovimientos.png", window),
        srcArea(0, 0, ANCHO_IMG_DUCK, ALTO_IMG_DUCK) {}

void DuckAnimacion::render() {
    Area destArea(x_des, y_des, ANCHO_IMG_DUCK, ALTO_IMG_DUCK);
    movimientos.render(srcArea, destArea);
}

void DuckAnimacion::mover_a_derecha() {
    x_des += 10;

    for (int x_img = 32; x_img <= ANCHO_IMG_DUCK_TOTAL; x_img += 32) {
        srcArea = Area(x_img, 0, ANCHO_IMG_DUCK, ALTO_IMG_DUCK);
        window.fill();
        this->render();
        window.render();
        SDL_Delay(300);
    }

    srcArea = Area(0, 0, ANCHO_IMG_DUCK, ALTO_IMG_DUCK);
}
