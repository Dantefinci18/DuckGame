#ifndef MAPA_H
#define MAPA_H

#include <string>

#include <vector>

#include "Sdl/SdlTexture.h"
#include "Sdl/SdlWindow.h"
#include "../server/Collidable.h"
#include "../server/Platform.h"
#include "../server/SpawnPlace.h"


/* 
 * Clase que se encarga de renderizar el mapa del juego
 */
class Mapa {
public:

    /*
     * Constructor de la clase Mapa, recibe una ventanam, la ruta del fondo y un vector de collidables
     */
    Mapa(SdlWindow& window, const std::string& ruta_fondo, std::vector<Collidable*> collidables);
    
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
    std::vector<Collidable*> collidables_plataformas; 


    const int FACTOR_ESCALA = 2;
    const int ALTO_VENTANA = 600;
    const int ANCHO_VENTANA = 800;
   
};

#endif