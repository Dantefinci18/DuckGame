#ifndef CLIENTE_H
#define CLIENTE_H

#include "cliente_sender.h"
#include "cliente_receiver.h"
#include "cliente_protocolo.h"
#include "DuckAnimacion.h"
#include "Sdl/SdlWindow.h"
#include <atomic>
#include "../common/common_queue.h"
#include "../common/common_evento.h"
#include "../common/common_accion.h"
#include <SDL2/SDL.h>


class Cliente {
    private:
        SdlWindow window;
        DuckAnimacion duck;
        ClienteProtocolo protocolo;
        ClienteReceiver receiver;
        int id;
        ClienteSender sender;
        Queue<Evento> queue_eventos;
        Queue<ComandoAccion> queue_acciones;
        std::atomic<bool> conectado {true};
        
        void ejecutar_juego();
        void procesar_eventos_recibidos();
        void enviar_accion(ComandoAccion *tecla_anterior, ComandoAccion accion);
        void controlar_eventos_del_teclado(ComandoAccion* tecla_anterior);
        void stop();
        void join();


    
    public:
        explicit Cliente(const char* hostname, const char* servname);
        void start();
        int generar_id();
};


#endif