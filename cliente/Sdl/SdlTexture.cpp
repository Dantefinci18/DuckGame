#include "SdlTexture.h"

#include <string>

#include <SDL2/SDL_image.h>

#include "Area.h"
#include "SdlException.h"
#include "SdlWindow.h"

SdlTexture::SdlTexture(const std::string& filename, const SdlWindow& window):
        renderer(window.getRenderer()) {
    this->texture = loadTexture(filename);
}

SdlTexture::~SdlTexture() { SDL_DestroyTexture(this->texture); }

SDL_Texture* SdlTexture::loadTexture(const std::string& filename) {
    SDL_Texture* texture = IMG_LoadTexture(this->renderer, filename.c_str());
    if (!texture) {
        throw SdlException("Error al cargar la textura", SDL_GetError());
    }
    return texture;
}

int SdlTexture::render(const Area& src, const Area& dest, SDL_RendererFlip flip, double angle, const SDL_Point* center) const {
    SDL_Rect sdlSrc = {src.getX(), src.getY(), src.getWidth(), src.getHeight()};
    SDL_Rect sdlDest = {dest.getX(), dest.getY(), dest.getWidth(), dest.getHeight()};

    return SDL_RenderCopyEx(this->renderer, this->texture, &sdlSrc, &sdlDest, angle, center, flip);
}

SDL_Texture* SdlTexture::getTexture() const {
    return texture;
}