#ifndef ENEMIGO_H
#define ENEMIGO_H

#include <string>
#include "duck.h"  
#include "Sdl/SdlWindow.h"
#include "../server/Collidable.h"
#include "../common/common_weapon.h"

class Enemigo {
public:

    /* 
     * Constructor de la clase Enemigo, recibe un id, un string con el color, un float con la posicion x, un float con la posicion y y una ventana
     */
    Enemigo(int id,std::string,float x, float y, SdlWindow& window);

    /* 
     * Funcion que retorna el id del enemigo
     */
    int get_id() const;

    /* 
     * Funcion que mueve al enemigo a una posicion x y y
     * Recibe un float con la nueva posicion x y un float con la nueva posicion y
     * Tambien recibe un booleano para saber si el pato esta aleteando.
     */
    void mover_a(float nueva_x, float nueva_y, bool is_flapping);
    
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
    
    /* 
     * Destructor de la clase Enemigo
     */
    ~Enemigo();

private:
    int id;  
    Duck duck; 
};

#endif // ENEMIGO_H