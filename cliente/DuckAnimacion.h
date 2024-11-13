#ifndef DUCKANIMACION_H
#define DUCKANIMACION_H

#define ANCHO_IMG_DUCK 32
#define ALTO_IMG_DUCK 38

#include <SDL2/SDL.h>
#include "Sdl/Area.h"
#include "Sdl/SdlTexture.h"
#include "Sdl/SdlWindow.h"
#include "../server/Collidable.h"
#include <vector>

class DuckAnimacion {
private:
    SdlTexture movimientos_en_x;  
    SdlTexture movimiento_en_y;   
    SdlTexture plataformas;        
    bool quieto = false;           
    int x_img = 0;                
    float x_actual;                
    float y_actual;                
    float x_des = x_actual;       
    int y_des = y_actual;         
    SDL_RendererFlip flip = SDL_FLIP_NONE;  
    std::vector<Collidable*> collidables_plataformas;  

public:
    explicit DuckAnimacion(SdlWindow& window, float x_inicial, float y_inicial);

    void render();

    bool esta_quieto();

    void mover_a_una_posicion(float x, float y);

    void set_collidables(const std::vector<Collidable*>& collidables);
};

#endif
