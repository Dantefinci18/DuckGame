#include <stdexcept>
#include "SdlText.h"
#include <SDL2/SDL_ttf.h>
#include "SdlWindow.h"
#include <iostream>
SdlText::SdlText(const std::string& text, const SdlWindow& window, int textWidth, int textHeight, int x, int y)
        : text(text), 
        renderer(window.getRenderer()), 
        texture(nullptr), 
        textWidth(textWidth), 
        textHeight(textHeight), 
        windowWidth(window.width), 
        windowHeight(window.height),
        x(x),
        y(y) {
    if (!renderer) {
        throw std::runtime_error("Renderer is null.");
    }
    createTexture();
}

SdlText::~SdlText() {
    if (texture) {
        SDL_DestroyTexture(texture);
    }
}

void SdlText::createTexture() {
    // Initialize TTF if not already done
    if (TTF_Init() == -1) {
        throw std::runtime_error("Failed to initialize TTF: " + std::string(TTF_GetError()));
    }

    // Load the font (update the font path and size as needed)
    TTF_Font* font = TTF_OpenFont("../Fonts/Halo Dek.ttf", 24);
    if (!font) {
        throw std::runtime_error("Failed to load font: " + std::string(TTF_GetError()));
    }

    SDL_Color color = {0, 0, 0, 0};
    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
    if (!surface) {
        TTF_CloseFont(font);
        throw std::runtime_error("Failed to create text surface: " + std::string(TTF_GetError()));
    }

    this->texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_FreeSurface(surface);
    TTF_CloseFont(font);

    if (!texture) {
        throw std::runtime_error("Failed to create texture: " + std::string(SDL_GetError()));
    }
}

void SdlText::render() const {
    if (!texture) {
        return; // Nothing to render
    }

    // Center the text on the screen
    SDL_Rect dstRect = {
        x,
        windowHeight - y,
        textHeight,
        textWidth
    };

    int ret = SDL_RenderCopyEx(this->renderer, this->texture, nullptr, &dstRect, 0 , nullptr, SDL_FLIP_NONE);
    if (ret != 0) {
        std::cout << "Failed!" << std::endl;
    }
}

void SdlText::set_text(std::string text) {
    this->text = text;
}

