#ifndef CLIENTE_H
#define CLIENTE_H

#include "cliente_sender.h"
#include "cliente_receiver.h"
#include "cliente_protocolo.h"
#include "estado.h"
#include <SDL2/SDL.h>


class Cliente {
    private:
        ClienteProtocolo protocolo;
        ClienteSender sender;
        ClienteReceiver receiver;
    
    public:
        explicit Cliente(const char* hostname, const char* servname);
        void start();
        void stop();
        void join();
        ~Cliente();
};


#endif