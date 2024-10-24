#include "server_receiver.h"

#include <sstream>
#include <string>

Receiver::Receiver(/*Queue<>& eventos,*/ ProtocoloServidor& protocolo):
        /*eventos(eventos),*/ protocolo(protocolo) {}

void Receiver::run() {
    try {
        while (_keep_running) {
            //Recibo los eventos y los pusheo en eventos
        }

    } catch (std::exception& e) {
        if (_keep_running)
            std::cerr << "Error: " << e.what() << "\n";
    }
}

bool Receiver::se_cerro() { return !_keep_running; }
