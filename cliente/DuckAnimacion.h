#ifndef DUCKANIMACION_H
#define DUCKANIMACION_H

#define ANCHO_IMG_DUCK 32
#define ALTO_IMG_DUCK 38

#include <SDL2/SDL.h>

#include "Sdl/Area.h"
#include "Sdl/SdlTexture.h"
#include "Sdl/SdlWindow.h"

class DuckAnimacion {
private:
    SdlTexture movimientos;
    bool quieto = false;
    int x_img = 0;
    float x_actual;
    float y_actual;
    float x_des = x_actual;
    int y_des = y_actual;
    SDL_RendererFlip flip = SDL_FLIP_NONE;

public:
    explicit DuckAnimacion(SdlWindow& window, float x_inicial, float y_inicial);
    void render();
    bool esta_quieto();
    void mover_a_una_posicion(float x, float y);
};

#endif
