#include "server_jugador.h"

#include <string>
#include <tuple>
#include <utility>

#include "../common/common_queue.h"
#include "server_protocolo.h"


Jugador::Jugador(Queue<std::shared_ptr<Accion>>& comandos, Socket&& conexion,int id):
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

void Jugador::reset(Queue<std::shared_ptr<Accion>>& comandos){
    receiver.reset_cola(comandos);
    sender.start();
}

Queue<std::unique_ptr<Evento>>& Jugador::get_cola_eventos(){
    return cola_eventos;
}

bool Jugador::enviar_partidas(std::list<Partida> &partidas){
    return protocolo.enviar_partidas(partidas);
}

void Jugador::enviar_evento(const Evento& evento){

    std::unique_ptr<Evento> evento_ptr;

    if(evento.get_tipo() == Evento::EventoEspera){
        std::cout<< "evento espera esta por enviarse\n";
        evento_ptr = std::make_unique<EventoEspera>();
    }

    std::lock_guard<std::mutex> lock(mtx);
    protocolo.enviar_estado(*evento_ptr);;
}