#ifndef DUCK_H
#define DUCK_H

#include <SDL2/SDL.h>
#include <optional>
#include "Sdl/Area.h"
#include "Sdl/SdlTexture.h"
#include "Sdl/SdlWindow.h"
#include "../server/Collidable.h"
#include "../common/common_weapon.h"

class Duck {
public:
    Duck(SdlWindow& window, float x_inicial, float y_inicial, std::string color);

    void render();
    bool esta_quieto();
    void mover_a(float nueva_x, float nueva_y);
    void set_weapon(WeaponType weapon);
    void kill();
    ~Duck();

private:
    void render_movimiento_horizontal();
    void render_movimiento_vertical();
    void render_idle();
    void render_movimiento_salto(Area& srcArea, Area& destArea);
    void render_arma(int y_renderizado);

    SdlTexture movimientos_en_x;
    SdlTexture movimiento_en_y;
    SdlTexture armas;
    SdlTexture death;
    bool quieto = false;
    bool is_dead = false;
    std::optional<WeaponType> weapon;
    int x_img = 0;
    int y_img = 0;
    float x_actual;
    float y_actual;
    float x_des;
    int y_des;
    SDL_RendererFlip flip = SDL_FLIP_NONE;
};

#endif // DUCK_H
