#ifndef MAPA_H
#define MAPA_H

#include <string>

#include <vector>

#include "Sdl/SdlTexture.h"
#include "Sdl/SdlWindow.h"
#include "../common/collidables/Collidable.h"
#include "../common/collidables/Platform.h"
#include "../common/collidables/SpawnPlace.h"
#include "../common/collidables/SpawnWeaponBox.h"
#include "../common/collidables/SpawnBox.h"
#include "../common/common_screen_utils.h"
/* 
 * Clase que se encarga de renderizar el mapa del juego
 */
class Mapa {
public:

    /*
     * Constructor de la clase Mapa, recibe una ventanam, la ruta del fondo y un vector de collidables
     */
    Mapa(SdlWindow& window, const std::string& ruta_fondo, std::vector<Collidable*> collidables);

     ~Mapa() = default;

    // Disable copying
    Mapa(const Mapa&) = delete;
    Mapa& operator=(const Mapa&) = delete;

    // Enable moving
    Mapa(Mapa&& other) noexcept;
    Mapa& operator=(Mapa&& other) noexcept;
    
    /*
     * Funcion que agrega un collidable al mapa
     * Recibe un puntero a un collidable
     */
    void agregar_collidable(Collidable* nuevo_collidable);

    /*
     * Funcion que elimina una caja
     * Recibe un float con la posicion x y un float con la posicion y
     */
    void eliminar_caja(float x, float y);

    /*
     * Funcion que limpia un arma
     * Recibe un puntero a un SpawnBox
     */
    void clear_weapon(SpawnBox* sWeaponBox);

    /* Renderiza el mapa
     */
    void renderizar_mapa();

    /* Renderiza el fondo
     */
    void render();
    /*
     * Funcion que setea los collidables del mapa
     * Recibe un vector de collidables
     */ 
    void set_collidables(const std::vector<Collidable*>& collidables);

private:
    SdlTexture fondo;
    SdlTexture plataformas;
    SdlTexture armas;
    SdlTexture armadura;
    SdlTexture casco;    
    SdlTexture boxes;  
    SdlTexture explosion;
    float x_expl;
    float y_expl;
    int width_expl;
    int height_expl;
    bool esta_explotando;
    std::vector<Collidable*> collidables_plataformas; 
};

#endif