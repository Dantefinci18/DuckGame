#ifndef DUCK_H
#define DUCK_H

#include <optional>
#include "../common/common_weapon.h"
#include "Sdl/SdlTexture.h"
#include "Sdl/SdlWindow.h"

class Duck {
public:
    Duck(SdlWindow& window,float x_inicial, float y_inicial, std::string color);

    void render();

    void mover_a_una_posicion(float x, float y);

    void set_weapon(WeaponType new_weapon);



    ~Duck();

private:
    SdlTexture movimientos_en_x;  
    SdlTexture movimiento_en_y;
    SdlTexture armas;  
    float x_actual, y_actual; 
    float x_des, y_des;
    int x_img = 0;               
    bool quieto;             
    std::optional<WeaponType> weapon;
    SDL_RendererFlip flip = SDL_FLIP_NONE;  


};

#endif // DUCK_H
