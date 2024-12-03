#include "cliente_mixer.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_log.h>

ClienteMixer::ClienteMixer() : musica_fondo(nullptr) {
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        SDL_Log("Error al inicializar SDL_mixer: %s", Mix_GetError());
    }
}

ClienteMixer::~ClienteMixer() {
    if (musica_fondo != nullptr) {
        Mix_FreeMusic(musica_fondo);
    }
    Mix_CloseAudio();
}

bool ClienteMixer::inicializar_mixer() {
    if (Mix_Init(MIX_INIT_MP3) == 0) {
        SDL_Log("Error al inicializar SDL_mixer: %s", Mix_GetError());
        return false;
    }
    return true;
}

bool ClienteMixer::cargar_y_reproducir_musica(const std::string& archivo, int repeticiones) {
    musica_fondo = Mix_LoadMUS(archivo.c_str());
    if (!musica_fondo) {
        SDL_Log("Error al cargar música de fondo: %s", Mix_GetError());
        return false;
    }

    if (Mix_PlayMusic(musica_fondo, repeticiones) == -1) {
        SDL_Log("Error al reproducir la música: %s", Mix_GetError());
        return false;
    }

    return true;
}

void ClienteMixer::reproducir_efecto_disparo(const std::string& archivo) {
    Mix_Chunk* sonido_bala = Mix_LoadWAV(archivo.c_str());
    if (!sonido_bala) {
        SDL_Log("Error al cargar el sonido de disparo: %s", Mix_GetError());
        return;
    }

    if (Mix_PlayChannel(-1, sonido_bala, 0) == -1) {
        SDL_Log("Error al reproducir el sonido de la bala: %s", Mix_GetError());
    }

    Mix_FreeChunk(sonido_bala);
}

void ClienteMixer::set_volumen(int volumen) {
    Mix_VolumeMusic(volumen);
}

void ClienteMixer::detener_musica() {
    Mix_HaltMusic();
}
