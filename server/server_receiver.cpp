#include "server_receiver.h"


#include <sstream>
#include <string>

Receiver::Receiver(ProtocoloServidor& protocolo, Queue<Accion>& acciones, int id):
        protocolo(protocolo), acciones(acciones), id(id) {}

void Receiver::run() {
    try {
        while (_keep_running) {
            ComandoAccion command = protocolo.recibir_accion();

            if(command == NONE){
                _keep_running = false;
                break;
            }
            Accion accion(id, command);
            acciones.push(std::move(accion));
        }

    } catch (std::exception& e) {
        if (_keep_running)
            std::cerr << "Error: " << e.what() << "\n";
    }
}

bool Receiver::se_cerro() { return !_keep_running; }
