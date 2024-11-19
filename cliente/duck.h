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
    /*
     * Constructor de la clase Duck, recibe una ventana, un float con la posicion x inicial, un float con la posicion y inicial y un string con el color
     */
    Duck(SdlWindow& window, float x_inicial, float y_inicial, std::string color);

    /* 
     * Funcion que renderiza al pato
     */
    void render();
    
    /* 
     * Funcion que retorna si el pato esta quieto
     */
    bool esta_quieto();

    /* 
     * Funcion que mueve al pato a una posicion x y y
     * Recibe un float con la nueva posicion x y un float con la nueva posicion y
     */ 
    void mover_a(float nueva_x, float nueva_y);

    /* 
     * Funcion que setea el arma del pato
     * Recibe un WeaponType
     */
    void set_weapon(WeaponType weapon);

    /* 
     * Funcion que mata al pato
     */
    void kill();

    /* 
     * Destructor de la clase Duck
     */
    ~Duck();

private:

    /* 
     * Funcion que renderiza el movimiento horizontal del pato
     */
    void render_movimiento_horizontal();

    /* 
     * Funcion que renderiza el movimiento vertical del pato
     */
    void render_movimiento_vertical();

    /* 
     * Funcion que renderiza al pato quieto
     */
    void render_idle();

    /* 
     * Funcion que renderiza el movimiento de salto del pato
     * Recibe un Area srcArea y un Area destArea
     */
    void render_movimiento_salto(Area& srcArea, Area& destArea);

    /* 
     * Funcion que renderiza el arma del pato
     * Recibe un int y_renderizado
     */
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
