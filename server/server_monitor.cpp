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
    for (auto cola : colas_de_eventos) {
        std::unique_ptr<Evento> evento_ptr = broadcast_evento(evento);
        cola->push(std::move(evento_ptr));
    }
}
