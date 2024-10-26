#ifndef DUCKANIMACION_H
#define DUCKANIMACION_H

#define ANCHO_IMG_DUCK 32
#define ALTO_IMG_DUCK 38

#include "../common/common_thread.h"
#include "Sdl/Area.h"
#include "Sdl/SdlTexture.h"
#include "Sdl/SdlWindow.h"
#include <SDL2/SDL.h>

class DuckAnimacion: public Thread {
private:
    SdlWindow& window;
    SdlTexture movimientos;
    bool moverse_a_derecha = false;
    bool moverse_a_izquierda = false;
    int x_img = 0;
    int x_des = 100;
    int y_des = 100;
    SDL_RendererFlip flip = SDL_FLIP_NONE;

public:
    explicit DuckAnimacion(SdlWindow& window);
    void run() override;
    void render();
    void dejar_de_moverse_a_derecha();
    void dejar_de_moverse_a_izquierda();
    void mover_a_derecha();
    void mover_a_izquierda();
};

#endif
