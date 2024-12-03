#include "SdlWindow.h"

#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>

#include "SdlException.h"


SdlWindow::SdlWindow(int width, int height): width(width), height(height) {
    int errCode = SDL_Init(SDL_INIT_VIDEO);
    if (errCode) {
        throw SdlException("Error en la inicialización", SDL_GetError());
    }
    errCode = SDL_CreateWindowAndRenderer(width, height, SDL_RENDERER_ACCELERATED, &this->window,
                                          &this->renderer);
    if (errCode) {
        throw SdlException("Error al crear ventana", SDL_GetError());
    }
    renderTarget = SDL_CreateTexture(this->renderer, SDL_PIXELFORMAT_BGRA8888, SDL_TEXTUREACCESS_TARGET, width, height);
}


SdlWindow::~SdlWindow() {
    if (this->renderer) {
        SDL_DestroyRenderer(this->renderer);
        this->renderer = nullptr;
    }

    if (this->window) {
        SDL_DestroyWindow(this->window);
        this->window = nullptr;
    }
}

void SdlWindow::fill(int r, int g, int b, int alpha) {
    SDL_SetRenderDrawColor(this->renderer, r, g, b, alpha);
    SDL_RenderClear(this->renderer);
}

void SdlWindow::fill() { this->fill(0x33, 0x33, 0x33, 0xFF); }

void SdlWindow::renderPortion(int x, int y, int w, int h) {
    SDL_SetRenderTarget(this->renderer, nullptr);
    SDL_Rect src =  {x, y, w, h};
    SDL_Rect dest = {0, 0, width, height};

    SDL_RenderCopy(this->renderer, renderTarget, &src, &dest);
}

void SdlWindow::render() { 
    SDL_RenderPresent(this->renderer); 
}

void SdlWindow::set_target_for_frame() {
    SDL_SetRenderTarget(this->renderer, renderTarget);
    SDL_SetRenderDrawColor(this->renderer, 0,0,0,255);
    SDL_RenderClear(this->renderer);
}
void SdlWindow::set_title(const char* titulo) { SDL_SetWindowTitle(window, titulo); }

SDL_Renderer* SdlWindow::getRenderer() const { return this->renderer; }
