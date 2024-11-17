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

void PlayerMonitor::broadcast_evento(const Evento& evento) {
    for (const auto& pair : jugadores) {
        pair.second->enviar_evento(evento); 
    }
}

Player* PlayerMonitor::get_player(int id) {
    return jugadores[id]->get_fisicas();
}

void PlayerMonitor::procesar_acciones(std::vector<Accion> acciones, std::vector<Collidable*> collidables) {
    for (auto& accion : acciones) {
        
        int id = accion.get_player_id();
        ComandoAccion command = accion.get_command();
        Player* player = get_player(id);
        if (command == DERECHA) {
            player->set_direction({1.0f, 0.0f});
        
        } else if (command == IZQUIERDA) {
            player->set_direction({-1.0f, 0.0f});
        
        } else if (command == SALTAR) {
            std::cout << "jumps" << std::endl;
            player->jump();
        
        } else if (command == QUIETO) {
            player->set_direction({0.0f, 0.0f});
        
        } else if (command == NUEVA_PARTIDA){
           EventoMapa eventoMapa(collidables);
              broadcast_evento(eventoMapa);
              return;
        }
    
    }

    for (auto& collidable : collidables) {
        collidable->update(collidables);
    }

    for (auto& player : jugadores) {
        
        Vector anterior = player.second->get_fisicas()->get_posicion();
        int id = player.first;

        player.second->update_fisicas(collidables);
        
        Vector pos_pato = player.second->get_fisicas()->get_posicion();

        if (anterior.x != pos_pato.x || anterior.y != pos_pato.y) {
            EventoMovimiento eventoMovimiento(id, pos_pato.x, pos_pato.y);
            
            broadcast_evento(eventoMovimiento);
        }
    }
}
