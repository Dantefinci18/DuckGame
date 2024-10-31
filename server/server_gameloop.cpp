#include "server_gameloop.h"
#include "../common/estado.h"

Gameloop::Gameloop(Queue<ComandoAccion> &comandos_acciones ,Monitor& monitor):
 comandos_acciones(comandos_acciones), monitor(monitor), player({100.0f, 150.0f}) {}

void Gameloop::run() {
    
    /*const float targetFPS = 5.0f;
    const float targetFrameTime = 1.0f / targetFPS;*/

    ComandoAccion accion;
    Vector anterior = player.get_posicion();

    while (_keep_running) {
        if(comandos_acciones.try_pop(accion)){
        //auto frameStartTime = std::chrono::high_resolution_clock::now();
        
            if (accion == DERECHA) {
                player.set_direction({1.0f, 0.0f});
            
            } else if (accion == IZQUIERDA) {
                player.set_direction({-1.0f, 0.0f});
            
            } else if (accion == SALTAR) {
                player.jump();
            
            } else if (accion == QUIETO) {
                player.set_direction({0.0f, 0.0f});
            
            }
        }
        
        player.move();
        Vector pos_pato = player.get_posicion();

        if(anterior.x != pos_pato.x)
            monitor.enviar_estado(pos_pato);
        
        anterior = pos_pato;
        ejecutar_eventos();
    }
}

void Gameloop::ejecutar_eventos() {

   std::this_thread::sleep_for(std::chrono::milliseconds(150));
}