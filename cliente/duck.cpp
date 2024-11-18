#include "duck.h"
#include <cmath>
#include <iostream>
#include "Sdl/SdlWindow.h"
#include "Sdl/Area.h"

#define ANCHO_IMG_DUCK 32
#define ALTO_IMG_DUCK 38
#define ANCHO_IMG_DUCK_TOTAL 180
#define ALTO_VENTANA 600
#define DESPLAZAMIENTO 3
#define DESPLAZAMIENTO_Y 4
#define FACTOR_ESCALA 2
#define VELOCIDAD_SALTO 5


Duck::Duck(SdlWindow& window, float x_inicial, float y_inicial, std::string color)
    : 
    movimientos_en_x("../Imagenes/movimiento_x" + color + ".png", window),
    movimiento_en_y("../Imagenes/movimiento_y" + color + ".png", window),
    armas("../Imagenes/guns.png", window),  
    x_actual(x_inicial),
    y_actual(y_inicial),
    x_des(x_inicial),
    y_des(y_inicial),
    x_img(0),
    quieto(true), 
    weapon(std::nullopt),
    flip(SDL_FLIP_NONE)
{}

void Duck::render() {

    if (x_actual < x_des) {
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
    }

    if (y_actual != y_des) {
        float distancia_vertical = y_des - y_actual;
        float velocidad_vertical = VELOCIDAD_SALTO * (distancia_vertical > 0 ? 1 : -1);

        if (std::abs(distancia_vertical) < VELOCIDAD_SALTO) {
            y_actual = y_des;
        } else {
            y_actual += velocidad_vertical;
        }

        if ((distancia_vertical > 0 && y_actual > y_des) || (distancia_vertical < 0 && y_actual < y_des)) {
            y_actual = y_des;
        }
    }

    int y_renderizado = ALTO_VENTANA - y_actual - ALTO_IMG_DUCK * FACTOR_ESCALA;
    
    Area srcArea(x_img, 0, ANCHO_IMG_DUCK, ALTO_IMG_DUCK);
    Area destArea(x_actual, y_renderizado, ANCHO_IMG_DUCK * FACTOR_ESCALA, ALTO_IMG_DUCK * FACTOR_ESCALA);
    
    if (y_actual != y_des) {
        movimiento_en_y.render(srcArea, destArea, flip); 
    } else {
        movimientos_en_x.render(srcArea, destArea, flip);  
    }
    
   

    if (x_actual == x_des && y_actual == y_des) {
        quieto = true;
    } else {
        quieto = false;
    }

    if (weapon) {
        Area armaSrcArea(0, 0, 38,38);  
        //TODO: Fix this
        Area armaDestArea(x_actual + 20, y_renderizado + 25, 38, 38); 
        armas.render(armaSrcArea, armaDestArea, flip);
    }
}



void Duck::mover_a_una_posicion(float x, float y) {
    if (x != x_des || y != y_des) {
        quieto = false;
    }
    x_des = x;
    y_des = y;
}


void Duck::set_weapon(WeaponType new_weapon) {
    weapon = new_weapon;
}

Duck::~Duck() {}