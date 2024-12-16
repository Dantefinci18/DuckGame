#include "server_jugador.h"

#include <string>
#include <tuple>
#include <utility>

#include "../common/common_queue.h"
#include "server_protocolo.h"


Jugador::Jugador(Queue<Accion>& comandos, Socket&& conexion,int id):
        protocolo(std::move(conexion)), 
        id(id),
        sender(protocolo, cola_eventos, id), 
        receiver(protocolo, comandos, id){
            protocolo.enviar_id(id);
        }

void Jugador::run() {
    receiver.start();
}

bool Jugador::esta_conectado() { return !receiver.se_cerro() && !sender.se_cerro(); }

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

int Jugador::generar_id() {
    std::random_device rd;
    std::mt19937 engine(rd());
    std::uniform_int_distribution<int> distribution(INT32_MIN, INT32_MAX);

    int id = distribution(engine);
    std::cout << id << std::endl;
    return id;
}

void Jugador::reset(Queue<Accion> &comandos){
    receiver.reset_cola(comandos);
    sender.start();
}

Queue<std::unique_ptr<Evento>>& Jugador::get_cola_eventos(){
    return cola_eventos;
}

void Jugador::enviar_evento(const Evento& evento){
    std::unique_ptr<Evento> evento_ptr;

    if (evento.get_tipo() == Evento::EventoEspera) {
        std::cout << "evento espera enviado\n";
        evento_ptr = std::make_unique<EventoEspera>();
    } else if (evento.get_tipo() == Evento::EventoPartidas) {
        std::cout << "Serializando partidas" << std::endl;
        evento_ptr = std::make_unique<EventoPartidas>(static_cast<const EventoPartidas&>(evento).partidas);
    } else {
        evento_ptr = evento.clone();
    }

    protocolo.enviar_estado(*evento_ptr);
}

int Jugador::recibir_cantidad_jugadores(){
    std::cout << "recibiendo cantidad de jugadores\n";
    return protocolo.recibir_cantidad_jugadores();
}
