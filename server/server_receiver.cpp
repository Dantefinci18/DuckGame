#include "server_receiver.h"


#include <sstream>
#include <string>

Receiver::Receiver(ProtocoloServidor& protocolo, Queue<Accion>& acciones, int id):
        protocolo(protocolo), acciones(&acciones), id(id) {}

void Receiver::run() {
    try {
        while (_keep_running) {
            ComandoAccion command = protocolo.recibir_accion();

            if (command == NUEVA_PARTIDA) {
                int cantidad_jugadores = protocolo.recibir_cantidad_jugadores();
                Accion accion(id, command,cantidad_jugadores);
                std::lock_guard<std::mutex> lock(mtx);
                acciones->push(std::move(accion));
            
            }
            else if (command == UNIRSE_PARTIDA) {
                int id_partida = protocolo.recibir_cantidad_jugadores();
                Accion accion(id, command, id_partida);
                std::lock_guard<std::mutex> lock(mtx);
                acciones->push(std::move(accion));
            }

            else if(command == NONE_ACCION){
                _keep_running = false;
                break;
            }
            else {
                Accion accion(id, command);
                std::lock_guard<std::mutex> lock(mtx);
                acciones->push(std::move(accion));
            }
       
        }

    } catch (std::exception& e) {
        if (_keep_running)
            std::cerr << "Error: " << e.what() << "\n";
    }
}

bool Receiver::se_cerro() { return !_keep_running; }

void Receiver::reset_cola(Queue<Accion>& comandos){
    std::lock_guard<std::mutex> lock(mtx);
    acciones = &comandos;
}