
#include "mapa.h"
#include "Sdl/Area.h"
#include "Sdl/SdlTexture.h"
#include "Sdl/SdlWindow.h"
#include "../server/Collidable.h"
#include "../server/Platform.h"
#include "../server/SpawnPlace.h"

Mapa::Mapa(SdlWindow& window, const std::string& ruta_fondo, std::vector<Collidable*> collidables)
    : 
    fondo(ruta_fondo, window),
    plataformas("../Imagenes/Tileset_Surface.png", window),
    armas("../Imagenes/guns.png", window),
    collidables_plataformas(collidables) {}

void Mapa::renderizar_mapa(){
     for (auto& collidable : this->collidables_plataformas) {
        if (collidable->getType() == CollidableType::Platform) {
            Platform* platform = static_cast<Platform*>(collidable);

            float plat_x = platform->position.x;  
            float plat_y = ALTO_VENTANA - platform->position.y - platform->height * FACTOR_ESCALA; 
            float plat_width = platform->width;   
            float plat_height = platform->height; 

            Area platformSrcArea(0, 0, 38,38);  
            Area platformDestArea(plat_x, plat_y, plat_width, plat_height);
            //std::cout << "plataforma_render" << std::endl; 
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
                //std::cout << "arma_render" << std::endl;
                armas.render(armaSrcArea, armaDestArea, SDL_FLIP_NONE);
            }
        }
    }
}

void Mapa::render() {
    Area srcArea(0, 0, ANCHO_VENTANA, ALTO_VENTANA);
    Area destArea(0, 0, ANCHO_VENTANA, ALTO_VENTANA);
    //std::cout << "fondo_render" << std::endl;
    fondo.render(srcArea, destArea, SDL_FLIP_NONE);

    renderizar_mapa();      
}

void Mapa::set_collidables(const std::vector<Collidable*>& collidables) {
    this->collidables_plataformas = collidables;
}

// Move constructor
Mapa::Mapa(Mapa&& other) noexcept
    : fondo(std::move(other.fondo)),
      plataformas(std::move(other.plataformas)),
      armas(std::move(other.armas)),
      collidables_plataformas(std::move(other.collidables_plataformas)) {}

// Move assignment operator
Mapa& Mapa::operator=(Mapa&& other) noexcept {
    if (this != &other) {
        fondo = std::move(other.fondo);
        plataformas = std::move(other.plataformas);
        armas = std::move(other.armas);
        collidables_plataformas = std::move(other.collidables_plataformas);
    }
    return *this;
}