#ifndef CLIENTE_MIXER_H
#define CLIENTE_MIXER_H

#include <string>
#include <SDL2/SDL_mixer.h>

class ClienteMixer {
public:
    ClienteMixer();  
    ~ClienteMixer();

    bool inicializar_mixer();

    bool cargar_y_reproducir_musica(const std::string& archivo, int repeticiones = -1);

    void reproducir_efecto_disparo(const std::string& archivo);

    void set_volumen(int volumen);

    void detener_musica();

private:
    Mix_Music* musica_fondo;  
};

#endif // CLIENTE_MIXER_H
