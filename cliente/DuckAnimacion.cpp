#define ANCHO_IMG_DUCK_TOTAL 400
#define DESPLAZAMIENTO 3
#define TIEMPO_EN_DEPLAZARSE 150

#include "DuckAnimacion.h"

#include <SDL2/SDL_render.h>

DuckAnimacion::DuckAnimacion(SdlWindow& window, float x_inicial, float y_inicial):
        window(window), 
        movimientos("../Imagenes/DuckMovimientos.png", window), 
        x_actual(x_inicial),
        y_actual(y_inicial) {}

void DuckAnimacion::run() {
    while (_keep_running) {
        if (x_actual < x_des) {
            x_actual = x_des;
            flip = SDL_FLIP_NONE;
            std::cout << x_actual << std::endl;
            if (x_img < ANCHO_IMG_DUCK_TOTAL) {
                x_img += ANCHO_IMG_DUCK;
                SDL_Delay(TIEMPO_EN_DEPLAZARSE);

            } else {
                x_img = 0;
            }

                //SDL_Delay(TIEMPO_EN_DEPLAZARSE);
        }else if(x_actual > x_des){
            x_actual = x_des;
            flip = SDL_FLIP_HORIZONTAL;

            if (x_img < ANCHO_IMG_DUCK_TOTAL) {
                x_img += ANCHO_IMG_DUCK;
                SDL_Delay(TIEMPO_EN_DEPLAZARSE);

            } else {
                x_img = 0;
            }
        
        }else{
            x_img = 0;
        }
    }
}


void DuckAnimacion::render() {
    Area srcArea(x_img, 0, ANCHO_IMG_DUCK, ALTO_IMG_DUCK);
    Area destArea(x_actual, y_actual, ANCHO_IMG_DUCK, ALTO_IMG_DUCK);
    
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

void DuckAnimacion::mover_a_una_posicion(float x, float y){
    /*if(x==x_des){
        moverse_a_derecha = false;
        moverse_a_izquierda = false;
        x_img = 0;
    
    }else{
        if(!moverse_a_derecha && x > x_des){
            mover_a_derecha();
        
        }else if(!moverse_a_izquierda && x < x_des){
            mover_a_izquierda();
        }*/
        
        x_des = x;
        y_des = y;
    //}
}
