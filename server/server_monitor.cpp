#include "server_monitor.h"
#include "DisparoManager.h"

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
            player->set_x_direction(1.0f);
        
        } else if (command == IZQUIERDA) {
            player->set_x_direction(-1.0f);
        
        } else if (command == SALTAR) {
            std::cout << "jumps" << std::endl;
            player->jump();
        
        } else if (command == QUIETO) {
            player->set_x_direction(0.0f);
        
        } else if (command == NUEVA_PARTIDA){
            EventoMapa eventoMapa(collidables);
            broadcast_evento(eventoMapa);
            return;
        } else if (command == DISPARAR){
            std::vector<std::shared_ptr<Evento>> eventos;
            if(player->has_weapon()){
                DisparoManager::procesar_disparo(*player, collidables, jugadores, eventos);
            }
            /*for (const auto& evento : eventos) {
                broadcast_evento(evento);
            } ACA ACTIVO CUANDO SUME LOS EVENTOS*/ 
        } else if (command == DEJAR_DISPARAR){
            std::cout << "Dejo de disparar" << std::endl;
            player->dejar_disparar();
        } else if (command == RECARGAR){
            player->reload();
        }
    
    }

    for (auto& collidable : collidables) {
        collidable->update(collidables);
        
        if (collidable->getType() == CollidableType::SpawnPlace) {
            SpawnPlace& sPlace = static_cast<SpawnPlace&>(*collidable);
            for (auto& evento : sPlace.eventos) {
                std::cout << "hereeee" << std::endl;
                broadcast_evento(*evento);
            }
            sPlace.eventos.clear();
        }
        
    }

    for (auto& player : jugadores) {
        player.second->update_fisicas(collidables);
    
        for (auto& evento : player.second->get_fisicas()->eventos) {
            broadcast_evento(*evento);
        }
        player.second->get_fisicas()->eventos.clear();
    }
}
