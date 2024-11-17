#ifndef DUCKANIMACION_H
#define DUCKANIMACION_H

#define ANCHO_IMG_DUCK 32
#define ALTO_IMG_DUCK 38

#include <SDL2/SDL.h>
#include "Sdl/Area.h"
#include "Sdl/SdlTexture.h"
#include "Sdl/SdlWindow.h"
#include "../server/Collidable.h"
#include "../common/common_weapon.h"
#include <vector>
#include <optional>

class DuckAnimacion {
private:
    SdlTexture movimientos_en_x;  
    SdlTexture movimiento_en_y;   
    SdlTexture plataformas; 
    SdlTexture armas;       
    bool quieto = false;
    std::optional<WeaponType> weapon;           
    int x_img = 0;                
    float x_actual;                
    float y_actual;                
    float x_des = x_actual;       
    int y_des = y_actual;         
    SDL_RendererFlip flip = SDL_FLIP_NONE;  
    std::vector<Collidable*> collidables_plataformas;
    void renderizar_mapa();

public:
    explicit DuckAnimacion(SdlWindow& window, float x_inicial, float y_inicial, std::vector<Collidable*> collidables);

    void render();

    bool esta_quieto();

    void mover_a_una_posicion(float x, float y);

    void set_collidables(const std::vector<Collidable*>& collidables);

    void set_weapon(WeaponType weapon);
};

#endif
