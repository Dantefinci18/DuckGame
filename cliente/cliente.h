#ifndef CLIENTE_H
#define CLIENTE_H

#include "cliente_sender.h"
#include "cliente_receiver.h"
#include "cliente_protocolo.h"
#include <atomic>
#include "../common/common_queue.h"
#include "../common/common_evento.h"
#include "../common/common_accion.h"
#include <SDL2/SDL.h>


class Cliente {
    private:
        ClienteProtocolo protocolo;
        ClienteSender sender;
        ClienteReceiver receiver;
        Queue<Evento> queue_eventos;
        Queue<ComandoAccion> queue_acciones;
        std::atomic<bool> conectado {true};
        void ingresar_accion(bool &conectado);
        void procesar_eventos(Evento &evento);


    
    public:
        explicit Cliente(const char* hostname, const char* servname);
        void start();
        void stop();
        void join();
};


#endif