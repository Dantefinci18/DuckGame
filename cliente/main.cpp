#include <SDL2/SDL.h>

#include "Sdl/SdlWindow.h"

int main() {
    SdlWindow window(800, 600);
    bool running = true;

    while (running) {
        SDL_Event event;
        SDL_WaitEvent(&event);

        if (event.type == SDL_QUIT) {
            running = false;
        }
    }

    window.render();
    return 0;
}
