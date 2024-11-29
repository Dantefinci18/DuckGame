#ifndef ENEMIGO_H
#define ENEMIGO_H

#include <string>
#include "duck.h"  
#include "Sdl/SdlWindow.h"
#include "../server/Collidable.h"
#include "../common/common_weapon.h"
#include "../common/common_direcciones.h"

class Enemigo {
public:

    /* 
     * Constructor de la clase Enemigo, recibe un id, un string con el color, un float con la posicion x, un float con la posicion y y una ventana
     */
    Enemigo(int id, ColorDuck color,int x, int y, SdlWindow& window);

    /* 
     * Funcion que retorna el id del enemigo
     */
    int get_id() const;

    /* 
     * Funcion que mueve al enemigo a una posicion x y y
     * Recibe un float con la nueva posicion x y un float con la nueva posicion y
     * Recibe un booleano para saber si el pato esta aleteando.
     * Recibe un booleano para saber si resetear la textura del pato.
     */
    void mover_a(int nueva_x, int nueva_y, bool is_flapping, bool reset);
    
    /* 
     * Funcion que renderiza al enemigo
     */
    void renderizar();

    /* 
     * Funcion que setea el arma del enemigo
     * Recibe un WeaponType
     */
    void set_weapon(WeaponType weapon);

    /*
    * Debe recibir una dirección valida.
    * Setea la dirección apuntada del enemigo
    */
    void apuntar_arma(DireccionApuntada direccion);

    /* 
     * Funcion que mata al enemigo
     */
    void kill();

    /* 
     * Funcion que agacha al enemigo
     */
    void agacharse();

    /* 
     * Funcion que levanta al enemigo
     */

    void levantarse();

    /* Funcion que devuelve el color del enemigo*/
    ColorDuck get_color();
    
    /* 
     * Destructor de la clase Enemigo
     */
    ~Enemigo();

private:
    int id;  
    Duck duck; 
};

#endif // ENEMIGO_H