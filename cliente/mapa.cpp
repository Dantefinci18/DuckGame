
#include "mapa.h"
#include "Sdl/Area.h"
#include "Sdl/SdlTexture.h"
#include "Sdl/SdlWindow.h"
#include "../server/Collidable.h"
#include "../server/Platform.h"
#include "../server/SpawnPlace.h"
#include "../server/Box.h"

Mapa::Mapa(SdlWindow& window, const std::string& ruta_fondo, std::vector<Collidable*> collidables)
    : 
    fondo(ruta_fondo, window),
    plataformas("../Imagenes/Tileset_Surface.png", window),
    armas("../Imagenes/guns.png", window),
    boxes("../Imagenes/box.png", window),
    explosion("../Imagenes/explosion.png", window),
    collidables_plataformas(collidables) {}

void Mapa::eliminar_caja(float x, float y) {
    //renderizar explosion en x e y
    Area srcArea(0, 0, 64, 64);
    Area destArea(x, ALTO_VENTANA - y, 64, 64);
    explosion.render(srcArea, destArea, SDL_FLIP_NONE);
    
    
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
                float plat_y = ALTO_VENTANA - spawnPlace->position.y - spawnPlace->height * FACTOR_ESCALA; 
                float plat_width = spawnPlace->width * FACTOR_ESCALA;   
                float plat_height = spawnPlace->height * FACTOR_ESCALA; 

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