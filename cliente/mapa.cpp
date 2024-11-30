
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
    /*
    plataformas("../Imagenes/Tileset_Surface.png", window),
    armas("../Imagenes/guns.png", window),
    boxes("../Imagenes/box.png", window),
    explosion("../Imagenes/explosion.png", window),
    */

    plataformas("../Imagenes/Tileset_Surface.png", window),
    armas("../Imagenes/guns.png", window),
    boxes("../Imagenes/box.png", window),
    explosion("../Imagenes/explosion.png", window),
    x_expl(0),
    y_expl(0),
    width_expl(0),
    height_expl(0),
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
                width_expl = box->width;
                height_expl = box->height;
                esta_explotando = true;
            }
        }
    }
    
    
}

void Mapa::clear_weapon(SpawnWeaponBox* sWeaponBox) {
    for (auto& collidable : this->collidables_plataformas) {
        if (collidable->getType() == CollidableType::SpawnWeaponBox) {
            SpawnWeaponBox* spawnBox = static_cast<SpawnWeaponBox*>(collidable);
            if (spawnBox->position.x == sWeaponBox->position.x && 
                spawnBox->position.y == sWeaponBox->position.y) {
                auto it = std::find(collidables_plataformas.begin(), collidables_plataformas.end(), collidable);
                if (it != collidables_plataformas.end()) {
                    collidables_plataformas.erase(it);
                }
                return; 
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
            float plat_y = ALTO_VENTANA - platform->position.y - platform->height; 
            float plat_width = platform->width;   
            float plat_height = platform->height; 
            Area platformSrcArea(5, 0, 38, 38);  
            Area platformDestArea(plat_x, plat_y, plat_width, plat_height); 
            plataformas.render(platformSrcArea, platformDestArea, SDL_FLIP_NONE);
        }

        if (collidable->getType() == CollidableType::SpawnPlace) {
            SpawnPlace* spawnPlace = static_cast<SpawnPlace*>(collidable);
            if (spawnPlace->has_weapon()) {
                float plat_x = spawnPlace->position.x;  
                float plat_y = ScreenUtils::get_y_for_screen(spawnPlace->position.y, spawnPlace->height);
                float plat_width = spawnPlace->width;   
                float plat_height = spawnPlace->height; 
                int arma_index = static_cast<int>(spawnPlace->get_weapon_type());
                Area armaSrcArea(arma_index * 38, 0, 38,38);  
                Area armaDestArea(plat_x, plat_y, plat_width, plat_height); 
                armas.render(armaSrcArea, armaDestArea, SDL_FLIP_NONE);
            }
        }

        if (collidable->getType() == CollidableType::Box) {
            Box* box = static_cast<Box*>(collidable);

            float box_x = box->position.x;
            float box_y = static_cast<float>(ScreenUtils::get_y_for_screen(box->position.y, box->height));

            Area boxSrcArea(0, 0, 16, 17);  
            Area boxDestArea(box_x, box_y, box->width, box->height); 

            boxes.render(boxSrcArea, boxDestArea, SDL_FLIP_NONE);
        }

        if (collidable->getType() == CollidableType::SpawnWeaponBox) {
            SpawnWeaponBox* spawnWeaponBox = static_cast<SpawnWeaponBox*>(collidable);

            float plat_x = spawnWeaponBox->position.x;
            float plat_y = static_cast<float>(ScreenUtils::get_y_for_screen(spawnWeaponBox->position.y, spawnWeaponBox->height));
            float plat_width = spawnWeaponBox->width;
            float plat_height = spawnWeaponBox->height;

            int arma_index = static_cast<int>(spawnWeaponBox->get_weapon_type());

            Area armaSrcArea(arma_index * 38, 0, 38, 38);
            Area armaDestArea(plat_x, plat_y, plat_width, plat_height);
            armas.render(armaSrcArea, armaDestArea, SDL_FLIP_NONE);
        }
        if (esta_explotando) {
            float box_x = x_expl;
            float box_y = ALTO_VENTANA - y_expl - height_expl;

            Area boxSrcArea(0, 0, 25, 22);
            Area boxDestArea(box_x, box_y, width_expl, height_expl);
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