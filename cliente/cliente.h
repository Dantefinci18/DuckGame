#ifndef CLIENTE_H
#define CLIENTE_H

#include "cliente_sender.h"
#include "cliente_receiver.h"
#include "cliente_protocolo.h"
#include "estado.h"
#include <atomic>
#include "../common/common_queue.h"
#include "../common/common_evento.h"
#include <SDL2/SDL.h>


class Cliente {
    private:
        ClienteProtocolo protocolo;
        ClienteSender sender;
        ClienteReceiver receiver;
        Queue<Evento> queue_eventos;
        std::atomic<bool> conectado {true};

    
    public:
        explicit Cliente(const char* hostname, const char* servname);
        void start();
        void stop();
        void join();
        ~Cliente();
};


#endif