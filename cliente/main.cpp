#define ANCHO_VENTANA 800
#define ALTO_VENTANA 600

#include <SDL2/SDL.h>

#include "Sdl/SdlWindow.h"

#include "DuckAnimacion.h"

int main() {
    SdlWindow window(ANCHO_VENTANA, ALTO_VENTANA);
    window.set_title("DuckGame");
    window.fill();
    DuckAnimacion duck(window);
    duck.start();
    bool running = true;

    while (running) {
        SDL_Event event;
        window.fill();
        duck.render();

        if (SDL_PollEvent(&event) == 1) {
            switch (event.type) {
                case SDL_QUIT:
                    running = false;
                    break;

                case SDL_KEYDOWN:
                    if (event.key.repeat == 0) {
                        const SDL_KeyboardEvent& keyEvent = (SDL_KeyboardEvent&)event;

                        if (keyEvent.keysym.sym == SDLK_RIGHT) {
                            duck.mover_a_derecha();
                        }
                    }

                    break;

                case SDL_KEYUP:
                    const SDL_KeyboardEvent& keyEvent = (SDL_KeyboardEvent&)event;
                    auto key = keyEvent.keysym.sym;

                    if (key == SDLK_RIGHT)
                        duck.quieto();

                    break;
            }
        }

        window.render();
    }

    duck.stop();
    duck.join();
    return 0;
}
