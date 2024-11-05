#include "server_monitor.h"

#include <iostream>
#include <string>

void PlayerMonitor::agregar_jugador(Jugador* jugador) {
    std::cout<<"agregando jugador" << std::endl;
    jugadores[jugador->get_id()] = jugador;
}
void PlayerMonitor::eliminar_jugador(int id) {
    std::cout <<"borrando jugador" << std::endl;
    jugadores.erase(id);
}

void PlayerMonitor::broadcast_evento(Evento evento) {
    for (const auto& pair : jugadores) {
        pair.second->enviar_evento(evento);
    }
}
Player* PlayerMonitor::get_player(int id) {
    return jugadores[id]->get_fisicas();
}

void PlayerMonitor::procesar_acciones(std::vector<Accion> acciones) {
    for (auto& accion : acciones) {
        
        int id = accion.get_player_id();
        ComandoAccion command = accion.get_command();
        Player* player = get_player(id);
        if (command == DERECHA) {
            player->set_direction({1.0f, 0.0f});
        
        } else if (command == IZQUIERDA) {
            player->set_direction({-1.0f, 0.0f});
        
        } else if (command == SALTAR) {
            player->jump();
        
        } else if (command == QUIETO) {
            player->set_direction({0.0f, 0.0f});
        
        }
    }

    // Update world
    for (auto& player : jugadores) {
        Vector anterior = player.second->get_fisicas()->get_posicion();
        int id = player.first;
        //TODO: Cambiar para pasarle todos los colisionables cuando los haya.
        player.second->update_fisicas(std::vector<Collidable*>());
        
        Vector pos_pato = player.second->get_fisicas()->get_posicion();
        // TODO: Metodo player.deberia_actualizar() para saber si enviar un evento
        
        //Por ahora si no se usa algo como x e y, o id2 ponerlo en 0
        if (anterior.x != pos_pato.x || anterior.y != pos_pato.y) {
            Evento evento;
            evento.tipo = MOVIMIENTO_JUGADOR;
            evento.x = pos_pato.x;
            evento.y = pos_pato.y;
            evento.id = id;
            evento.id_2 = 0;
            broadcast_evento(evento);
        }
    }
}
