#include "server_aceptador.h"

#include <sstream>
#include <string>
#include <tuple>
#include <utility>

#include "../common/common_liberror.h"

Aceptador::Aceptador(Socket& skt):skt(skt) {}

void Aceptador::run() {
    lobby.start();
    while (_keep_running) {
        try {

            Socket conexion = skt.accept();
            std::cout << "acepto una conexion\n";
            lobby.agregar_jugador(conexion);

        } catch (const LibError& e) {}
    }

    lobby.finalizar();
}