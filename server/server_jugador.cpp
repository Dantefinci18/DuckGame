#include "server_jugador.h"

#include <string>
#include <tuple>
#include <utility>

#include "../common/common_queue.h"
#include "server_protocolo.h"


Jugador::Jugador(Queue<Accion>& comandos, Queue<std::unique_ptr<Evento>>& cola_eventos, Socket&& conexion):
        protocolo(std::move(conexion)), 
        id(generar_id()),
        cola_eventos(cola_eventos),
        sender(protocolo, cola_eventos, id), 
        receiver(protocolo, comandos, id){}

void Jugador::run() {
    sender.start();
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
}

Queue<std::unique_ptr<Evento>>& Jugador::get_cola_eventos(){
    return cola_eventos;
}

void Jugador::enviar_evento(const Evento& evento){

    std::unique_ptr<Evento> evento_ptr;

    if(evento.get_tipo() == Evento::EventoEspera){
        std::cout<< "evento espera enviado\n";
        evento_ptr = std::make_unique<EventoEspera>();
    }

    cola_eventos.push(std::move(evento_ptr));
}