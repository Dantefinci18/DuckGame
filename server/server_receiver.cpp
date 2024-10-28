#include "server_receiver.h"


#include <sstream>
#include <string>

Receiver::Receiver(ProtocoloServidor& protocolo, Queue<ComandoAccion>& acciones):
        acciones(acciones), protocolo(protocolo) {}

void Receiver::run() {
    try {
        while (_keep_running) {
            ComandoAccion accion = protocolo.recibir_accion();
            acciones.push(accion);
        }

    } catch (std::exception& e) {
        if (_keep_running)
            std::cerr << "Error: " << e.what() << "\n";
    }
}

bool Receiver::se_cerro() { return !_keep_running; }
