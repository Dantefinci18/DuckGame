#define ANCHO_VENTANA 800
#define ALTO_VENTANA 600

#include <SDL2/SDL.h>

#include "Sdl/SdlWindow.h"
#include "Sdl/SdlTexture.h"
//#include "Sdl/Area.h"
#include "DuckAnimacion.h"


int main() {
    SdlWindow window(ANCHO_VENTANA, ALTO_VENTANA);
    window.set_title("DuckGame");
    SdlTexture fondo("../Imagenes/Fondo.png",window);
    Area srcArea(0,0,ANCHO_VENTANA,ALTO_VENTANA);
    Area destArea(0,0,ANCHO_VENTANA,ALTO_VENTANA);
    fondo.render(srcArea,destArea,SDL_FLIP_NONE);
    DuckAnimacion duck(window);
    duck.start();
    bool running = true;

    while (running) {
        SDL_Event event;
        fondo.render(srcArea,destArea,SDL_FLIP_NONE);
        duck.render();

        if (SDL_PollEvent(&event) == 1) {
            switch (event.type) {
                case SDL_QUIT:
                    running = false;
                    break;

                case SDL_KEYDOWN:
                    if (event.key.repeat == 0) {
                        const SDL_KeyboardEvent& keyEvent = (SDL_KeyboardEvent&)event;

                        switch (keyEvent.keysym.sym){ 
                            case SDLK_RIGHT:
                                duck.mover_a_derecha();
                                break;
                            
                            case SDLK_LEFT:
                                duck.mover_a_izquierda();
                                break;
                        }
                    }

                    break;

                case SDL_KEYUP:
                    const SDL_KeyboardEvent& keyEvent = (SDL_KeyboardEvent&)event;
                    auto key = keyEvent.keysym.sym;

                    switch(key){ 
                        
                        case SDLK_RIGHT:
                            duck.dejar_de_moverse_a_derecha();
                            break;
                        
                        case SDLK_LEFT:
                            duck.dejar_de_moverse_a_izquierda();
                    
                    }
                    
                    break;
            }
        }

        window.render();
    }

    duck.stop();
    duck.join();
    return 0;
}
