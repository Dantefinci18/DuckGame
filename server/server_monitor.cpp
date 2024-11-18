#include "server_monitor.h"

#include <iostream>
#include <string>

void PlayerMonitor::agregar_cola_evento(Queue<std::unique_ptr<Evento>>& cola_evento) {
    colas_de_eventos.push_back(&cola_evento);
}
void PlayerMonitor::eliminar_cola_evento(Queue<std::unique_ptr<Evento>>& cola_evento) {
    colas_de_eventos.remove(&cola_evento);
}

std::unique_ptr<Evento> PlayerMonitor::broadcast_evento(const Evento& evento){
    std::unique_ptr<Evento> evento_ptr;

    switch (evento.get_tipo()) {
        case Evento::EventoMovimiento: {
            const EventoMovimiento& evento_movimiento = static_cast<const EventoMovimiento&>(evento);
            evento_ptr = std::make_unique<EventoMovimiento>(evento_movimiento.id, evento_movimiento.x, evento_movimiento.y);
            break;
        }
        case Evento::EventoMapa: {
            
            const EventoMapa& evento_mapa = static_cast<const EventoMapa&>(evento);
            evento_ptr = std::make_unique<EventoMapa>(evento_mapa.collidables);
            break;
        }

        case Evento::EventoPickup: {
            
            const EventoPickup& evento_pickup = static_cast<const EventoPickup&>(evento);
            evento_ptr = std::make_unique<EventoPickup>(evento_pickup.id, evento_pickup.x, evento_pickup.y, evento_pickup.weapon_type);
            break;
        }

        case Evento::EventoSpawnArma: {
            
            const EventoSpawnArma& evento_spawn = static_cast<const EventoSpawnArma&>(evento);
            evento_ptr = std::make_unique<EventoSpawnArma>(evento_spawn.x, evento_spawn.y, evento_spawn.weapon_type);
            break;
        }
     
    }

    return evento_ptr;
}

void PlayerMonitor::enviar_evento(const Evento& evento) {
    std::unique_ptr<Evento> evento_ptr = broadcast_evento(evento);
    for (auto cola : colas_de_eventos) {
        cola->push(std::move(evento_ptr));
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
