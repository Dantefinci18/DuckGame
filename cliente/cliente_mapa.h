#ifndef MAPA_H
#define MAPA_H

#include <string>
#include <vector>
#include "Sdl/SdlTexture.h"
#include "Sdl/SdlWindow.h"
#include "../server/Collidable.h"
#include "../server/Platform.h"
#include "../server/SpawnPlace.h"

class Mapa {
public:
    Mapa(SdlWindow& window, const std::string& ruta_fondo, std::vector<Collidable*> collidables);

    void renderizar_mapa();
    void render();
    
    void set_collidables(const std::vector<Collidable*>& collidables);

private:
    SdlTexture fondo;
    SdlTexture plataformas;
    SdlTexture armas;           
    std::vector<Collidable*> collidables_plataformas; 

    void render_fondo();

    const int FACTOR_ESCALA = 2;
    const int alto_ventana = 600;
    const int ancho_ventana = 800;
   
};

#endif
