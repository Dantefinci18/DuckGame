#include "cliente_receiver.h"

ClienteReceiver::ClienteReceiver(ClienteProtocolo &protocolo, Queue<std::unique_ptr<Evento>> &queue_eventos, std::atomic<bool> &cliente_conectado)
    : protocolo(protocolo), queue_eventos(queue_eventos), cliente_conectado(cliente_conectado), id(-1) {}

void ClienteReceiver::run() {
    
    while (_keep_running) {
        try {
            std::unique_ptr<Evento> evento = protocolo.recibir_evento();
            std::cout << "evento_receiver" << std::endl;
            evento->print();
            if (evento) {
                queue_eventos.push(std::move(evento));  
            } else {
                _keep_running = false;
            }
        } catch (const std::exception &e) {
            if (_keep_running) {
                std::cerr << "Error: " << e.what() << "\n";
            }
        }
    }
    
    cliente_conectado = false;
}

int ClienteReceiver::get_id() {
    return id;
}
