#ifndef DUCKANIMACION_H
#define DUCKANIMACION_H

#define ANCHO_IMG_DUCK 32
#define ALTO_IMG_DUCK 38

#include "../common/common_thread.h"
#include "Sdl/Area.h"
#include "Sdl/SdlTexture.h"
#include "Sdl/SdlWindow.h"

class DuckAnimacion: public Thread {
private:
    SdlWindow& window;
    SdlTexture movimientos;
    bool moverse_a_derecha = false;
    int x_img = 0;
    int x_des = 100;
    int y_des = 100;

public:
    explicit DuckAnimacion(SdlWindow& window);
    void run() override;
    void render();
    void quieto();
    void mover_a_derecha();
};

#endif
