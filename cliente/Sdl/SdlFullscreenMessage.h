#ifndef __SDL_MESSAGE_H__
#define __SDL_MESSAGE_H__
#include <string>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "SdlWindow.h"

struct SDL_Texture;
struct SDL_Renderer;
struct SdlWindow;

class SdlFullscreenMessage {
public:
    /**
     * Crea un SDL_Texture, lanza una excepción si el filename es inválido
     **/
    explicit SdlFullscreenMessage(const std::string& text, const SdlWindow& window);
    /**
     * Libera la memoria reservada por la textura
     **/
    ~SdlFullscreenMessage();
    /**
     * Renderiza la textura cargada
     **/
    void render() const;



private:
    std::string text;           // The message text
    SDL_Renderer* renderer;     // The renderer for the SDL window
    SDL_Texture* texture;       // The texture for the rendered text
    int textWidth;              // The width of the text texture
    int textHeight;            // The height of the text texture
    int windowHeight;
    int windowWidth;
    /**
     * Helper function to create the texture from the text.
     **/
    void createTexture();
};

#endif
