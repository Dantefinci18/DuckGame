#include "cliente_mapa.h"
#include <SDL2/SDL_render.h>
#include "Sdl/Area.h"

#define ANCHO_VENTANA 800
#define ALTO_VENTANA 600

Mapa::Mapa(SdlWindow& window, const std::string& ruta_fondo, std::vector<Collidable*> collidables)
    : 
    fondo(ruta_fondo, window),
    plataformas("../Imagenes/Tileset_Surface.png", window),
    armas("../Imagenes/guns.png", window),
    collidables_plataformas(collidables) {}

    
void Mapa::render_fondo() {
    Area srcArea(0, 0, ANCHO_VENTANA, ALTO_VENTANA);
    Area destArea(0, 0, ANCHO_VENTANA, ALTO_VENTANA);
    fondo.render(srcArea, destArea, SDL_FLIP_NONE);
}


void Mapa::renderizar_mapa(){
     for (auto& collidable : this->collidables_plataformas) {
        if (collidable->getType() == CollidableType::Platform) {
            Platform* platform = static_cast<Platform*>(collidable);

            float plat_x = platform->position.x;  
            float plat_y = alto_ventana - platform->position.y - platform->height * FACTOR_ESCALA; 
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
                float plat_y = alto_ventana - spawnPlace->position.y - spawnPlace->height * FACTOR_ESCALA; 
                float plat_width = spawnPlace->width * FACTOR_ESCALA;   
                float plat_height = spawnPlace->height * FACTOR_ESCALA; 

                Area armaSrcArea(0, 0, 38,38);  
                Area armaDestArea(plat_x, plat_y, plat_width, plat_height); 
                armas.render(armaSrcArea, armaDestArea, SDL_FLIP_NONE);
            }
        }
    }
}

void Mapa::render() {
    render_fondo();
    renderizar_mapa();  

}

void Mapa::set_collidables(const std::vector<Collidable*>& collidables) {
    this->collidables_plataformas = collidables;
}
