#include <stdexcept>
#include "SdlText.h"
#include <SDL2/SDL_ttf.h>
#include "SdlWindow.h"
#include <iostream>
SdlText::SdlText(const std::string& text, const SdlWindow& window, int textWidth, int textHeight)
        : text(text), 
        renderer(window.getRenderer()), 
        texture(nullptr), 
        textWidth(textWidth), 
        textHeight(textHeight), 
        windowWidth(window.width), 
        windowHeight(window.height) {
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

    // Render the text into an SDL_Surface
    SDL_Color color = {0, 0, 0, 0}; // White color
    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
    if (!surface) {
        TTF_CloseFont(font);
        throw std::runtime_error("Failed to create text surface: " + std::string(TTF_GetError()));
    }

    // Convert the surface into an SDL_Texture
    texture = SDL_CreateTextureFromSurface(renderer, surface);

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

    // Get window dimensions (use hardcoded values or get them dynamically)
    int windowWidth = 800;
    int windowHeight = 600;

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

