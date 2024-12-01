#include "server_sender.h"
#include <string>

Sender::Sender(ProtocoloServidor& protocolo, Queue<std::unique_ptr<Evento>>& cola_eventos, int id)
    : protocolo(protocolo), cola_eventos(cola_eventos), id(id) {}

void Sender::enviar_eventos() {
    while (_keep_running) {
        std::unique_ptr<Evento> estado = cola_eventos.pop();  

        if(estado->get_tipo() == Evento::EventoEspera){
            std::cout << "evento espera en sender" << std::endl;
        }else{
            std::cout << "se envia otra cosa en sender" << std::endl;
        }

        if (estado) {
            protocolo.enviar_estado(*estado);
        }else{
          std::cout << "evento en sender es null" << std::endl;  
        }
    }
}
void Sender::stop() {
    _keep_running = false;
    cola_eventos.close();
}

void Sender::run() {
    //monitor.agregar_cola_evento(cola_eventos);
    try {
        enviar_eventos();
    } catch (std::exception& e) {
        if (_keep_running)
            std::cerr << "Error de escritura: " << e.what() << "\n";
    }
    //monitor.eliminar_cola_evento(cola_eventos);
}

bool Sender::se_cerro() {
    return !_keep_running;
}
