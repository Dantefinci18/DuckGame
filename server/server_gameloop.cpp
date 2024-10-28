#include "server_gameloop.h"
#include "../common/estado.h"

Gameloop::Gameloop(Queue<ComandoAccion> &comandos_acciones ,Monitor& monitor):
 comandos_acciones(comandos_acciones), monitor(monitor) {}

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