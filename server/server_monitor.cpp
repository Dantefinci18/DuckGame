#include "server_monitor.h"
#include "DisparoManager.h"

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
            evento_ptr = std::make_unique<EventoMovimiento>(evento_movimiento.id,evento_movimiento.color ,evento_movimiento.x, evento_movimiento.y, evento_movimiento.is_flapping);
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

        case Evento::EventoDisparo: {
            
            const EventoDisparo& evento_disparo = static_cast<const EventoDisparo&>(evento);
            evento_ptr = std::make_unique<EventoDisparo>(evento_disparo.id);
            break;
        }

        case Evento::EventoMuerte: {
            
            const EventoMuerte& evento_muerte = static_cast<const EventoMuerte&>(evento);
            evento_ptr = std::make_unique<EventoMuerte>(evento_muerte.id);
            break;
        }

        case Evento::EventoAgacharse: {
            
            const EventoAgacharse& evento_agacharse = static_cast<const EventoAgacharse&>(evento);
            evento_ptr = std::make_unique<EventoAgacharse>(evento_agacharse.id);
            break;
        }

        case Evento::EventoLevantarse: {
            
            const EventoLevantarse& evento_levantarse = static_cast<const EventoLevantarse&>(evento);
            evento_ptr = std::make_unique<EventoLevantarse>(evento_levantarse.id);
            break;
     
        }

        case Evento::EventoEspera: {
            evento_ptr = std::make_unique<EventoEspera>();
            break;
        }

        case Evento::EventoApuntar: {
            const EventoApuntar& evento_apuntar = static_cast<const EventoApuntar&>(evento);
            evento_ptr = std::make_unique<EventoApuntar>(evento_apuntar.id, evento_apuntar.direccion);
            break;
        }

        case Evento::EventoBala: {
            const EventoBala& evento_bala = static_cast<const EventoBala&>(evento);
            evento_ptr = std::make_unique<EventoBala>(evento_bala.x, evento_bala.y);
            break;
    
        }

        case Evento::EventoCajaDestruida: {
            const EventoCajaDestruida& evento_caja_destruida = static_cast<const EventoCajaDestruida&>(evento);
            evento_ptr = std::make_unique<EventoCajaDestruida>(evento_caja_destruida.x, evento_caja_destruida.y);
            break;
        }

        default: {
            std::cerr << "Error: Tipo de evento desconocido" << std::endl;
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
