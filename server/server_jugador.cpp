#include "server_jugador.h"

#include <string>
#include <tuple>
#include <utility>

#include "../common/common_queue.h"
#include "server_protocolo.h"


Jugador::Jugador(Queue<Accion>& comandos, PlayerMonitor& monitor, Socket&& conexion, ColorDuck color):
        protocolo(std::move(conexion)), 
        id(generar_id()),
        sender(protocolo, monitor, id), 
        receiver(protocolo, comandos, id),
        playerPhysics({200.0f,300.0f}, id, color) {}

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





Jugador::~Jugador() {}

