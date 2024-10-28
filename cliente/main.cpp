#define ANCHO_VENTANA 800
#define ALTO_VENTANA 600

#include <SDL2/SDL.h>
#include <iostream>
#include "Sdl/SdlWindow.h"
#include "Sdl/SdlTexture.h"
#include "DuckAnimacion.h"
#include "cliente.h"

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Cantidad de argumentos invalida" << std::endl;
        return 1;
    }

    const char* hostname = argv[1];
    const char* servname = argv[2];

    SdlWindow window(ANCHO_VENTANA, ALTO_VENTANA);
    window.set_title("DuckGame");
    SdlTexture fondo("../Imagenes/Fondo.png", window);
    Area srcArea(0, 0, ANCHO_VENTANA, ALTO_VENTANA);
    Area destArea(0, 0, ANCHO_VENTANA, ALTO_VENTANA);
    fondo.render(srcArea, destArea, SDL_FLIP_NONE);

    DuckAnimacion duck(window);
    duck.start();

    Cliente cliente(hostname, servname);
    cliente.start();

    duck.stop();
    duck.join();

    return 0;
}
