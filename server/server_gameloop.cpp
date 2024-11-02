#include "server_gameloop.h"
#include "../common/common_evento.h"

Gameloop::Gameloop(Queue<Accion> &comandos_acciones, PlayerMonitor& monitor):
 comandos_acciones(comandos_acciones), monitor(monitor) {}

void Gameloop::run() {
    
    /*const float targetFPS = 5.0f;
    const float targetFrameTime = 1.0f / targetFPS;*/

    /*
    Accion accion;
    while (_keep_running) {
        if(comandos_acciones.try_pop(accion)){
            int id = accion.get_player_id();
            ComandoAccion command = accion.get_command();
            Player player = monitor.get_player(id);
            Vector anterior = player.get_posicion();
            if (command == DERECHA) {
                player.set_direction({1.0f, 0.0f});
            
            } else if (command == IZQUIERDA) {
                player.set_direction({-1.0f, 0.0f});
            
            } else if (command == SALTAR) {
                player.jump();
            
            } else if (command == QUIETO) {
                player.set_direction({0.0f, 0.0f});
            
            }

            Vector pos_pato = player.get_posicion();
            //player.print_position();
            if(anterior.x != pos_pato.x) {
                Evento evento;
                evento.id = id;
                evento.x = pos_pato.x;
                evento.y = pos_pato.y;
                monitor.broadcast_evento(evento);
            }
            anterior = pos_pato;
        }
        monitor.update_fisicas();
        sleep();
    }*/

    while (_keep_running) {
        procesar_acciones();
        sleep();
    }
}

void Gameloop::procesar_acciones() {
    std::vector<Accion> acciones;
    Accion accion;
    bool tried = comandos_acciones.try_pop(accion);
    while (tried) {
        acciones.push_back(accion);
        tried = comandos_acciones.try_pop(accion);
    }
    monitor.procesar_acciones(acciones);
}

void Gameloop::sleep() {
   std::this_thread::sleep_for(std::chrono::milliseconds(150));
}