#ifndef __SDL_TEXTURE_H__
#define __SDL_TEXTURE_H__
#include <string>
#include <SDL2/SDL_render.h>

struct SDL_Texture;
struct SDL_Renderer;
struct SdlWindow;
class Area;

class SdlTexture {
public:
    /**
     * Crea un SDL_Texture, lanza una excepción si el filename es inválido
     **/
    SdlTexture(const std::string& filename, const SdlWindow& window);
    /**
     * Libera la memoria reservada por la textura
     **/
    ~SdlTexture();
    /**
     * Renderiza la textura cargada
     **/
    int render(const Area& src, const Area& dest, SDL_RendererFlip flip) const;

private:
    SDL_Texture* loadTexture(const std::string& filename);
    SDL_Renderer* renderer;
    SDL_Texture* texture;
};

#endif
