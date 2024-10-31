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
    
    Cliente cliente(hostname, servname);
    cliente.start();
    //SDL_Quit(); 
    return 0;
}

