#ifndef DUCK_H
#define DUCK_H

#include <SDL2/SDL.h>
#include <optional>
#include "Sdl/Area.h"
#include "Sdl/SdlTexture.h"
#include "Sdl/SdlWindow.h"
#include "../server/Collidable.h"
#include "../common/common_weapon.h"
#include "../common/common_color.h"
#include "../common/common_direcciones.h"

class Duck {
public:
    /*
     * Constructor de la clase Duck, recibe una ventana, un float con la posicion x inicial, un float con la posicion y inicial y un string con el color
     */
    Duck(SdlWindow& window, float x_inicial, float y_inicial, ColorDuck color);

    /* 
     * Funcion que setea la bala del pato
     * Recibe un float con la posicion x y un float con la posicion y
     */
    void setear_bala(float x, float y);
    

    void render_bala();

    /* 
     * Funcion que setea la bala del pato
     * Recibe un float con la posicion x y un float con la posicion y
     */
    void setear_bala(float x, float y);
    

    void render_bala();

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
     * Recibe un float con la nueva posicion x y un float con la nueva posicion y.
     * Recibe si en esta nueva posicion el pato esta aleteando
     * Recibe un booleano para saber si resetear la textura del pato.
     */ 
    void mover_a(float nueva_x, float nueva_y, bool is_flapping, bool reset);

    /*
     * Funcion que debe recibir una direccion valida 
     */
    void apuntar_arma(DireccionApuntada direccion);

    /*
     * Funcion que debe recibir una direccion valida 
     */
    void apuntar_arma(DireccionApuntada direccion);

    /* 
     * Funcion que agacha al pato
     */
    void agacharse();

    /* 
     * Funcion que levanta al pato
     */
    void levantarse();


    /* 
     * Funcion que setea el arma del pato
     * Recibe un WeaponType
     */
    void set_weapon(WeaponType weapon);

    /* 
     * Funcion que mata al pato
     */
    void kill();

    /* Devuelve el color del pato */
    ColorDuck get_color();

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

    /* Dado un color devuelve un string */
    std::string procesar_color(ColorDuck color);

    

    SdlTexture movimientos_en_x;
    SdlTexture movimiento_en_y;
    SdlTexture armas;
    SdlTexture death;
    ColorDuck color;
    SdlTexture bala;
    bool quieto;
    std::optional<WeaponType> weapon;
    DireccionApuntada direccion_arma;
    int x_img = 0;
    int y_img = 0;
    float x_actual;
    float y_actual;
    bool is_dead;
    float x_des;
    int y_des;
    float x_bala;
    float y_bala;
    bool esta_disparando;
    bool is_flapping;
    bool esta_agachado;
    bool reset;
    SDL_RendererFlip flip;

};

#endif // DUCK_H
