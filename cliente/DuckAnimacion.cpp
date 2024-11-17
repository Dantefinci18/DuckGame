#define ANCHO_IMG_DUCK_TOTAL 180
#define ALTO_VENTANA 600
#define DESPLAZAMIENTO 3
#define DESPLAZAMIENTO_Y 4
#define FACTOR_ESCALA 2
#define VELOCIDAD_SALTO 5

#include "DuckAnimacion.h"
#include <SDL2/SDL_render.h>
#include "../server/Platform.h"
#include "../server/SpawnPlace.h"

DuckAnimacion::DuckAnimacion(SdlWindow& window, float x_inicial, float y_inicial, std::vector<Collidable*> collidables)
    : movimientos_en_x("../Imagenes/DuckMovimientos.png", window),
      movimiento_en_y("../Imagenes/DuckSalto.png", window),
      plataformas("../Imagenes/Tileset_Surface.png", window),
      armas("../Imagenes/guns.png", window),
      x_actual(x_inicial),
      y_actual(y_inicial),
      x_des(x_inicial),
      y_des(y_inicial),
      x_img(0),
      quieto(true),
      weapon(std::nullopt),
      flip(SDL_FLIP_NONE),
      collidables_plataformas(collidables) {}

void DuckAnimacion::renderizar_mapa(){
     for (auto& collidable : this->collidables_plataformas) {
        if (collidable->getType() == CollidableType::Platform) {
            Platform* platform = static_cast<Platform*>(collidable);

            float plat_x = platform->position.x;  
            float plat_y = ALTO_VENTANA - platform->position.y - platform->height * FACTOR_ESCALA; 
            float plat_width = platform->width;   
            float plat_height = platform->height; 

            Area platformSrcArea(0, 0, 38,38);  
            Area platformDestArea(plat_x, plat_y, plat_width, plat_height); 
            plataformas.render(platformSrcArea, platformDestArea, SDL_FLIP_NONE);
        }

        if (collidable->getType() == CollidableType::SpawnPlace) {
            SpawnPlace* spawnPlace = static_cast<SpawnPlace*>(collidable);
            if (spawnPlace->has_weapon()) {
                float plat_x = spawnPlace->position.x;  
                float plat_y = ALTO_VENTANA - spawnPlace->position.y - spawnPlace->height * FACTOR_ESCALA; 
                float plat_width = spawnPlace->width * FACTOR_ESCALA;   
                float plat_height = spawnPlace->height * FACTOR_ESCALA; 

                Area armaSrcArea(0, 0, 38,38);  
                Area armaDestArea(plat_x, plat_y, plat_width, plat_height); 
                armas.render(armaSrcArea, armaDestArea, SDL_FLIP_NONE);
            }
        }
    }
}

void DuckAnimacion::render() {
    renderizar_mapa();

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



bool DuckAnimacion::esta_quieto() { return quieto; }

void DuckAnimacion::mover_a_una_posicion(float x, float y) {
    if (x != x_des || y != y_des) {
        quieto = false;
    }
    x_des = x;
    y_des = y;
}

void DuckAnimacion::set_collidables(const std::vector<Collidable*>& collidables) {
    std::cout << "Agregando collidables " << collidables.size() << std::endl;
    this->collidables_plataformas = collidables;  
}

void DuckAnimacion::set_weapon(WeaponType new_weapon) {
    weapon = new_weapon;
}

