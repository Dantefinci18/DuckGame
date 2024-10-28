#include "cliente.h"
#include "../common/common_queue.h"
#include "../common/common_evento.h"

Cliente::Cliente(const char* hostname, const char* servname) : protocolo(hostname, servname), receiver(protocolo, queue_eventos,conectado),sender(protocolo) {}

void Cliente::start(){

    receiver.run();
    sender.run();
    while (conectado){
        //SDL_Event evento;
    }
    stop();
    join();
   
}

void Cliente::stop(){
    receiver.stop();
    sender.stop();
    protocolo.cerrar_conexion();
    queue_eventos.close();
}

void Cliente::join(){
    receiver.join();
    sender.join();
}

Cliente::~Cliente(){}