#include "server_jugador.h"

#include <string>
#include <tuple>
#include <utility>

#include "../common/common_queue.h"
#include "server_protocolo.h"

Jugador::Jugador(Queue<ComandoAccion>& comandos,Monitor& monitor,
                 Socket&& conexion):
        protocolo(std::move(conexion)), sender(protocolo, monitor),receiver(protocolo, comandos) {}

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
