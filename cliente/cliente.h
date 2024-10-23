#ifndef CLIENTE_H
#define CLIENTE_H

#include "cliente_sender.h"
#include "cliente_reciver.h"
#include "cliente_protocolo.h"
#include "estado.h"
#include <SDL2/SDL.h>


class Cliente {
    private:
        ClienteProtocolo protocolo;
        ClienteSender sender;
        ClienteReciver reciver;
    
    public:
        explicit Cliente(const char* hostname, const char* servname);
        void enviar_comando(const SDL_KeyboardEvent& ket_event);
        Estado recibir_estado();
};


#endif