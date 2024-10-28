#include "cliente.h"
#include "../common/common_queue.h"
#include "../common/common_evento.h"

Cliente::Cliente(const char* hostname, const char* servname) : protocolo(hostname, servname), receiver(protocolo, queue_eventos,conectado),sender(protocolo, queue_acciones) {}

void Cliente::start(){

    receiver.run();
    sender.run();
    while (conectado){
        ingresar_accion(conectado);
    }
    stop();
    join();
   
}

void Cliente::ingresar_accion(bool conectado) {
    SDL_Event evento;
    
    while (SDL_PollEvent(&evento)) { 
        switch (evento.type) {
            case SDL_QUIT:
                conectado = false;
                break;
            case SDL_KEYDOWN:
                switch (evento.key.keysym.sym) {
                    case SDLK_LEFT:
                        queue_acciones.push(ComandoAccion::IZQUIERDA);
                        break;
                    case SDLK_RIGHT:
                        queue_acciones.push(ComandoAccion::DERECHA);
                        break;
                    default:
                        break;
                }
                break;
            case SDL_KEYUP:
                switch (evento.key.keysym.sym) {
                    case SDLK_LEFT:
                        queue_acciones.push(ComandoAccion::STOP_IZQUIERDA);
                        break;
                    case SDLK_RIGHT:
                        queue_acciones.push(ComandoAccion::STOP_DERECHA);
                        break;
                    default:
                        break;
                }
                break;
            default:
                break;
        }
    }
}


void Cliente::stop(){
    receiver.stop();
    sender.stop();
    protocolo.cerrar_conexion();
    queue_eventos.close();
    queue_acciones.close();
}

void Cliente::join(){
    receiver.join();
    sender.join();
}

Cliente::~Cliente(){}