#include "server_sender.h"

#include <string>

Sender::Sender(ProtocoloServidor& protocolo, Queue<Evento>& cola_eventos, int id):
        protocolo(protocolo), cola_eventos(cola_eventos), id(id) {}

void Sender::enviar_eventos() {
    protocolo.enviar_id(id);
    while (_keep_running) {
        Evento estado = cola_eventos.pop();
        protocolo.enviar_estado(estado);
    }
}


void Sender::stop() {
    _keep_running = false;
    cola_eventos.close();
}

void Sender::run() {
    try {
        enviar_eventos();
    } catch (std::exception& e) {
        if (_keep_running)
            std::cerr << "Error de escritura: " << e.what() << "\n";
    }
}

bool Sender::se_cerro() { return !_keep_running; }
