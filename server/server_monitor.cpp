#include "server_monitor.h"
#include "DisparoManager.h"

#include <iostream>
#include <string>

void PlayerMonitor::agregar_cola_evento(Queue<std::unique_ptr<Evento>>& cola_evento) {
    std::lock_guard<std::mutex> lock(mtx);
    colas_de_eventos.push_back(&cola_evento);
}

void PlayerMonitor::eliminar_cola_evento(Queue<std::unique_ptr<Evento>>& cola_evento) {
    std::lock_guard<std::mutex> lock(mtx);
    colas_de_eventos.remove(&cola_evento);
}

std::unique_ptr<Evento> PlayerMonitor::broadcast_evento(const Evento& evento){
    std::unique_ptr<Evento> evento_ptr;

    switch (evento.get_tipo()) {
        case Evento::EventoMovimiento: {
            const EventoMovimiento& evento_movimiento = static_cast<const EventoMovimiento&>(evento);
            evento_ptr = std::make_unique<EventoMovimiento>(evento_movimiento.id, evento_movimiento.color ,evento_movimiento.x, evento_movimiento.y, evento_movimiento.is_flapping, evento_movimiento.reset);
            break;
        }
        case Evento::EventoMapa: {
            const EventoMapa& evento_mapa = static_cast<const EventoMapa&>(evento);
            evento_ptr = std::make_unique<EventoMapa>(evento_mapa.collidables, evento_mapa.leaderboard);
            break;
        }

        case Evento::EventoPickup: {
            const EventoPickup& evento_pickup = static_cast<const EventoPickup&>(evento);
            evento_ptr = std::make_unique<EventoPickup>(evento_pickup.id, evento_pickup.x, evento_pickup.y, evento_pickup.weapon_type);
            break;
        }

        case Evento::EventoPickupProteccion: {
            const EventoPickupProteccion& evento_pickup_proteccion = static_cast<const EventoPickupProteccion&>(evento);
            evento_ptr = std::make_unique<EventoPickupProteccion>(evento_pickup_proteccion.id, evento_pickup_proteccion.x, evento_pickup_proteccion.y, evento_pickup_proteccion.proteccion_type);
            break;
        }

        case Evento::EventoSpawnArma: {
            std::cout << "spawn_arma" << std::endl;
            const EventoSpawnArma& evento_spawn = static_cast<const EventoSpawnArma&>(evento);
            evento_ptr = std::make_unique<EventoSpawnArma>(evento_spawn.x, evento_spawn.y, evento_spawn.weapon_type);
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
            const EventoEspera& evento_espera = static_cast<const EventoEspera&>(evento);
            evento_ptr = std::make_unique<EventoEspera>(evento_espera.id_partida);
            break;
        }

        case Evento::EventoWinRound: {
            const EventoWinRound& evento_win_round = static_cast<const EventoWinRound&>(evento);
            evento_ptr = std::make_unique<EventoWinRound>(evento_win_round.id);
            break;
        }

        case Evento::EventoWinMatch: {
            const EventoWinMatch& evento_win_match = static_cast<const EventoWinMatch&>(evento);
            evento_ptr = std::make_unique<EventoWinMatch>(evento_win_match.id);
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

        case Evento::EventoSpawnArmaBox: {
            const EventoSpawnArmaBox& evento_spawn_arma_box = static_cast<const EventoSpawnArmaBox&>(evento);
            evento_ptr = std::make_unique<EventoSpawnArmaBox>(evento_spawn_arma_box.x, evento_spawn_arma_box.y, evento_spawn_arma_box.width, evento_spawn_arma_box.height, evento_spawn_arma_box.weapon_type);
            break;
        }

        case Evento::EventoSpawnProteccionBox: {
            const EventoSpawnProteccionBox& evento_spawn_proteccion_box = static_cast<const EventoSpawnProteccionBox&>(evento);
            evento_ptr = std::make_unique<EventoSpawnProteccionBox>(evento_spawn_proteccion_box.x, evento_spawn_proteccion_box.y, evento_spawn_proteccion_box.proteccion_type);
            break;
        }

        case Evento::EventoPartidas: {
            const EventoPartidas& evento_partidas = static_cast<const EventoPartidas&>(evento);
            evento_ptr = std::make_unique<EventoPartidas>(evento_partidas.partidas);
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
    std::lock_guard<std::mutex> lock(mtx);
    for (auto cola : colas_de_eventos) {
        std::unique_ptr<Evento> evento_ptr = evento.clone();
        cola->push(std::move(evento_ptr));
    }
}
