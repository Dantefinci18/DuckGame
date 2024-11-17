#include "server_sender.h"
#include <string>

Sender::Sender(ProtocoloServidor& protocolo, Queue<std::unique_ptr<Evento>>& cola_eventos, int id)
    : protocolo(protocolo), cola_eventos(cola_eventos), id(id) {}

void Sender::enviar_eventos() {
    protocolo.enviar_id(id);
    while (_keep_running) {
        std::unique_ptr<Evento> estado = cola_eventos.pop();  

        if (estado) {
            protocolo.enviar_estado(*estado);
            /*
            switch (estado->get_tipo()) {
                case Evento::EventoMovimiento:
                    protocolo.enviar_estado(*static_cast<EventoMovimiento*>(estado.get()));
                    break;

                case Evento::EventoMapa:
                    protocolo.enviar_estado(*static_cast<EventoMapa*>(estado.get()));
                    break;

                default:
                    std::cerr << "Error: Tipo de evento desconocido" << std::endl;
                    break;
            }
            */
        }
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

bool Sender::se_cerro() {
    return !_keep_running;
}
