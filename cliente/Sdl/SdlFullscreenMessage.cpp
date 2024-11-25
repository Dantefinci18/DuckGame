#include <stdexcept>
#include "SdlFullscreenMessage.h"
#include <SDL2/SDL_ttf.h>
#include "SdlWindow.h"
#include <iostream>
SdlFullscreenMessage::SdlFullscreenMessage(const std::string& text, const SdlWindow& window)
    : text(text), renderer(window.getRenderer()), texture(nullptr), textWidth(0), textHeight(0), windowWidth(window.width), windowHeight(window.height) {
    if (!renderer) {
        throw std::runtime_error("Renderer is null.");
    }

    createTexture();
}

SdlFullscreenMessage::~SdlFullscreenMessage() {
    if (texture) {
        SDL_DestroyTexture(texture);
    }
}

void SdlFullscreenMessage::createTexture() {
    // Initialize TTF if not already done
    if (TTF_Init() == -1) {
        throw std::runtime_error("Failed to initialize TTF: " + std::string(TTF_GetError()));
    }

    // Load the font (update the font path and size as needed)
    TTF_Font* font = TTF_OpenFont("../Fonts/Halo Dek.ttf", 24);
    if (!font) {
        throw std::runtime_error("Failed to load font: " + std::string(TTF_GetError()));
    }

    // Render the text into an SDL_Surface
    SDL_Color color = {255, 255, 255, 255}; // White color
    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
    if (!surface) {
        TTF_CloseFont(font);
        throw std::runtime_error("Failed to create text surface: " + std::string(TTF_GetError()));
    }

    // Convert the surface into an SDL_Texture
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    textWidth = surface->w;
    textHeight = surface->h;

    SDL_FreeSurface(surface);
    TTF_CloseFont(font);

    if (!texture) {
        throw std::runtime_error("Failed to create texture: " + std::string(SDL_GetError()));
    }
}

void SdlFullscreenMessage::render() const {
    if (!texture) {
        return; // Nothing to render
    }

    // Render a semi-transparent black rectangle over the entire window
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 128); // Black with 50% transparency
    SDL_Rect overlayRect = {0, 0, windowWidth, windowHeight};
    SDL_RenderFillRect(renderer, &overlayRect);

    // Center the text on the screen
    SDL_Rect dstRect = {
        (windowWidth - textWidth) / 2,
        (windowHeight - textHeight) / 2,
        textWidth,
        textHeight
    };

    // Render the text texture
    SDL_RenderCopy(renderer, texture, nullptr, &dstRect);
}

