#include "server_sender.h"
#include <string>

Sender::Sender(ProtocoloServidor& protocolo, PlayerMonitor& monitor, int id)
    : protocolo(protocolo), monitor(monitor), id(id) {}

void Sender::enviar_eventos() {
    protocolo.enviar_id(id);
    while (_keep_running) {
        std::unique_ptr<Evento> estado = cola_eventos.pop();  

        if (estado) {
            protocolo.enviar_estado(*estado);
        }
    }
}
void Sender::stop() {
    _keep_running = false;
    cola_eventos.close();
}

void Sender::run() {
    monitor.agregar_cola_evento(cola_eventos);
    try {
        enviar_eventos();
    } catch (std::exception& e) {
        if (_keep_running)
            std::cerr << "Error de escritura: " << e.what() << "\n";
    }
    monitor.eliminar_cola_evento(cola_eventos);
}

bool Sender::se_cerro() {
    return !_keep_running;
}
