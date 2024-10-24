#include "server_sender.h"

#include <string>

Sender::Sender(ProtocoloServidor& protocolo, Monitor& monitor):
        protocolo(protocolo), monitor(monitor) {}

void Sender::enviar_estados() {
    while (_keep_running) {
        //enviar estados
    }
}


void Sender::stop() {
    _keep_running = false;
    cola_estados.close();
}

void Sender::run() {
    monitor.agregar_queue(cola_estados);

    try {
        enviar_estados();

    } catch (std::exception& e) {
        if (_keep_running)
            std::cerr << "Error de escritura: " << e.what() << "\n";
    }

    monitor.eliminar_queue(cola_estados);
}

bool Sender::se_cerro() { return !_keep_running; }
