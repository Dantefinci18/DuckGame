#include "server_aceptador.h"

#include <sstream>
#include <string>
#include <tuple>
#include <utility>

#include "../common/common_liberror.h"

Aceptador::Aceptador(Socket& skt):skt(skt),lobby(0) {}

void Aceptador::run() {
    lobby.start();
    while (_keep_running) {
        try {
            Socket conexion = skt.accept();
            lobby.agregar_jugador(conexion);

        } catch (const LibError& e) {}
    }

    lobby.finalizar();
}