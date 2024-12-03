#include "server_receiver.h"


#include <sstream>
#include <string>

Receiver::Receiver(ProtocoloServidor& protocolo, Queue<std::shared_ptr<Accion>>& acciones, int id):
        protocolo(protocolo), acciones(&acciones), id(id) {}

void Receiver::run() {
    try {
        while (_keep_running) {
            std::shared_ptr<Accion> accion = protocolo.recibir_accion();
            accion->print();
            if(accion->get_command() == NONE_ACCION){
                _keep_running = false;
                break;
            }
            
            accion->set_player_id(id);
            std::lock_guard<std::mutex> lock(mtx);
            acciones->push(std::move(accion));
        }

    } catch (std::exception& e) {
        if (_keep_running)
            std::cerr << "Error: " << e.what() << "\n";
    }
}

bool Receiver::se_cerro() { return !_keep_running; }

void Receiver::reset_cola( Queue<std::shared_ptr<Accion>>& comandos){
    std::lock_guard<std::mutex> lock(mtx);
    acciones = &comandos;
}