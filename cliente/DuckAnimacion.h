#ifndef DUCKANIMACION_H
#define DUCKANIMACION_H

#define ANCHO_IMG_DUCK 32
#define ALTO_IMG_DUCK 38

#include "Sdl/Area.h"
#include "Sdl/SdlTexture.h"
#include "Sdl/SdlWindow.h"

class DuckAnimacion {
private:
    SdlWindow& window;
    SdlTexture movimientos;
    Area srcArea;
    int x_des = 100;
    int y_des = 100;

public:
    explicit DuckAnimacion(SdlWindow& window);
    void render();
    void quieto();
    void mover_a_derecha();
};

#endif
