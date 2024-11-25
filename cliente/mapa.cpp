
#include "mapa.h"
#include "Sdl/Area.h"
#include "Sdl/SdlTexture.h"
#include "Sdl/SdlWindow.h"
#include "../server/Collidable.h"
#include "../server/Platform.h"
#include "../server/SpawnPlace.h"
#include "../server/SpawnWeaponBox.h"
#include "../server/Box.h"

Mapa::Mapa(SdlWindow& window, const std::string& ruta_fondo, std::vector<Collidable*> collidables)
    : 
    fondo(ruta_fondo, window),
    plataformas("../Imagenes/Tileset_Surface.png", window),
    armas("../Imagenes/guns.png", window),
    boxes("../Imagenes/box.png", window),
    explosion("../Imagenes/explosion.png", window),
    x_expl(0),
    y_expl(0),
    esta_explotando(false),
    collidables_plataformas(collidables) {}

void Mapa::eliminar_caja(float x, float y) {
    for (auto& collidable: this->collidables_plataformas){
        if (collidable->getType() == CollidableType::Box){
            Box* box = static_cast<Box*>(collidable);
            if (box->position.x == x && box->position.y == y){
                auto it = std::find(collidables_plataformas.begin(), collidables_plataformas.end(), collidable);
                if (it != collidables_plataformas.end()) {
                    collidables_plataformas.erase(it); 
                }
                x_expl = x;
                y_expl = y;
                esta_explotando = true;
            }
        }
    }
    
    
}

void Mapa::clear_weapon(SpawnWeaponBox* sWeaponBox) {
    for (auto& collidable : this-> collidables_plataformas) {
        if (collidable->getType() == CollidableType::SpawnWeaponBox) {
            SpawnWeaponBox* sWeaponBox = static_cast<SpawnWeaponBox*>(collidable);
            if (sWeaponBox->position.x == sWeaponBox->position.x && sWeaponBox->position.y == sWeaponBox->position.y) {
                auto it = std::find(collidables_plataformas.begin(), collidables_plataformas.end(), collidable);
                if (it != collidables_plataformas.end()) {
                    collidables_plataformas.erase(it);
                }
            }
        }
    }
}

void Mapa::agregar_collidable(Collidable* nuevo_collidable) {
    collidables_plataformas.push_back(nuevo_collidable);
}

void Mapa::renderizar_mapa() {
    for (auto& collidable : this->collidables_plataformas) {
        if (collidable->getType() == CollidableType::Platform) {
            Platform* platform = static_cast<Platform*>(collidable);

            float plat_x = platform->position.x;  
            float plat_y = ALTO_VENTANA - platform->position.y - platform->height * FACTOR_ESCALA; 
            float plat_width = platform->width;   
            float plat_height = platform->height; 

            Area platformSrcArea(0, 0, 38, 38);  
            Area platformDestArea(plat_x, plat_y, plat_width, plat_height); 
            plataformas.render(platformSrcArea, platformDestArea, SDL_FLIP_NONE);
        }

        if (collidable->getType() == CollidableType::SpawnPlace) {
            SpawnPlace* spawnPlace = static_cast<SpawnPlace*>(collidable);
            if (spawnPlace->has_weapon()) {
                float plat_x = spawnPlace->position.x;  
                float plat_y = ALTO_VENTANA - spawnPlace->position.y - spawnPlace->height * FACTOR_ESCALA_ARMA; 
                float plat_width = spawnPlace->width * FACTOR_ESCALA_ARMA;   
                float plat_height = spawnPlace->height * FACTOR_ESCALA_ARMA; 

                Area armaSrcArea(0, 0, 38, 38);  
                Area armaDestArea(plat_x, plat_y, plat_width, plat_height); 
                armas.render(armaSrcArea, armaDestArea, SDL_FLIP_NONE);
            }
        }

        if (collidable->getType() == CollidableType::Box) {
            Box* box = static_cast<Box*>(collidable);

            float box_x = box->position.x;  
            float box_y = ALTO_VENTANA - box->position.y - 28 * FACTOR_ESCALA_BOX; 
            float box_width = 28 * FACTOR_ESCALA_BOX;  
            float box_height = 28 * FACTOR_ESCALA_BOX;

            Area boxSrcArea(0, 0, 28, 28);  
            Area boxDestArea(box_x, box_y, box_width, box_height); 
            boxes.render(boxSrcArea, boxDestArea, SDL_FLIP_NONE);
        }

        if (collidable->getType() == CollidableType::SpawnWeaponBox) {
            SpawnWeaponBox* spawnWeaponBox = static_cast<SpawnWeaponBox*>(collidable);

            float plat_x = spawnWeaponBox->position.x;
            float plat_y = ALTO_VENTANA - spawnWeaponBox->position.y - spawnWeaponBox->height * FACTOR_ESCALA_ARMA;
            float plat_width = spawnWeaponBox->width * FACTOR_ESCALA_ARMA;
            float plat_height = spawnWeaponBox->height * FACTOR_ESCALA_ARMA;

            Area armaSrcArea(0, 0, 38, 38);
            Area armaDestArea(plat_x, plat_y, plat_width, plat_height);
            armas.render(armaSrcArea, armaDestArea, SDL_FLIP_NONE);
        }
        if (esta_explotando) {
            float box_x = x_expl;
            float box_y = ALTO_VENTANA - y_expl - 28 * FACTOR_ESCALA_BOX;
            float box_width = 28 * FACTOR_ESCALA_BOX;
            float box_height = 28 * FACTOR_ESCALA_BOX;

            Area boxSrcArea(0, 0, 28, 28);
            Area boxDestArea(box_x, box_y, box_width, box_height);
            explosion.render(boxSrcArea, boxDestArea, SDL_FLIP_NONE);
            esta_explotando = false;

        }
    }
}


void Mapa::render() {
    Area srcArea(0, 0, ANCHO_VENTANA, ALTO_VENTANA);
    Area destArea(0, 0, ANCHO_VENTANA, ALTO_VENTANA);
    fondo.render(srcArea, destArea, SDL_FLIP_NONE);

    renderizar_mapa();  

    
}

void Mapa::set_collidables(const std::vector<Collidable*>& collidables) {
    this->collidables_plataformas = collidables;
}