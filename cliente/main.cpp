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
    bool running = true;

    while (running) {
        SDL_Event event;
        window.fill();
        duck.render();
        SDL_WaitEvent(&event);

        switch (event.type) {
            case SDL_QUIT:
                running = false;
                break;

            case SDL_KEYDOWN:
                const SDL_KeyboardEvent& keyEvent = (SDL_KeyboardEvent&)event;

                if (keyEvent.keysym.sym == SDLK_RIGHT)
                    duck.mover_a_derecha();

                break;
        }

        window.render();
    }

    return 0;
}
