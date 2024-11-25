#ifndef __SDL_TEXT_H__
#define __SDL_TEXT_H__
#include <string>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "SdlWindow.h"

struct SDL_Texture;
struct SDL_Renderer;
struct SdlWindow;

class SdlText {
public:
    /**
     * Crea un SdlText: recibe un x y un y con el 0,0 abajo a la izquierda de la ventana
     **/
    explicit SdlText(const std::string& text, const SdlWindow& window, 
        const int text_height, const int text_width, int x, int y);
    /**
     * Libera la memoria reservada por la textura
     **/
    ~SdlText();
    /**
     * Renderiza el text dados los parametros pasados.
     **/
    void render() const;

    void set_text(std::string text);

private:
    std::string text;           // The message text
    SDL_Renderer* renderer;     // The renderer for the SDL window
    SDL_Texture* texture;       // The texture for the rendered text
    int textWidth;              // The width of the text texture
    int textHeight;             // The height of the text texture
    int windowWidth;
    int windowHeight;
    int x;
    int y;
    /**
     * Helper function to create the texture from the text.
     **/
    void createTexture();
};

#endif
