#include "server_jugador.h"

#include <string>
#include <tuple>
#include <utility>

#include "../common/common_queue.h"
#include "server_protocolo.h"

Jugador::Jugador(Queue<Accion>& comandos, Socket&& conexion):
        protocolo(std::move(conexion)), 
        cola_eventos(), 
        id(generar_id()),
        sender(protocolo, cola_eventos, id), 
        receiver(protocolo, comandos, id),
        playerPhysics({200.0f,300.0f}, id) {}

void Jugador::run() {
    sender.start();
    receiver.start();
}

bool Jugador::esta_conectado() { return !receiver.se_cerro() && !sender.se_cerro(); }

void Jugador::enviar_evento(const Evento& evento) {
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

        default:
            return; 
    }

    cola_eventos.try_push(std::move(evento_ptr));
}

void Jugador::stop() {
    receiver.stop();
    sender.stop();
    receiver.join();
    sender.join();
}

void Jugador::cerrar_conexion() { protocolo.cerrar_conexion(); }

int Jugador::get_id() {
    return id;
}

Player* Jugador::get_fisicas() {
    return &playerPhysics;
}

void Jugador::update_fisicas(std::vector<Collidable*> collidables) {
    //TODO: Refactor this so it receives all of the collidables.
    playerPhysics.update(collidables);
}

int Jugador::generar_id() {
    std::random_device rd;
    std::mt19937 engine(rd());
    std::uniform_int_distribution<int> distribution(INT32_MIN, INT32_MAX);

    int id = distribution(engine);
    std::cout << id << std::endl;
    return id;
}
