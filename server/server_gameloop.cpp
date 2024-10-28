#include "server_gameloop.h"
#include "../common/estado.h"

Gameloop::Gameloop(/*Queue<>& eventos,*/ Monitor& monitor):
    /*eventos(eventos),*/ monitor(monitor) {}

void Gameloop::ejecutar_eventos() {

 //while (eventos.try_pop(evento)) {
        
        Estado estado;  //Le doy un evento a la clae de la logica de juego y me devuelve un estado
        monitor.enviar_estado(estado);
    //}
}


void Gameloop::run() {
    while (_keep_running) {
        ejecutar_eventos();
    }
}
