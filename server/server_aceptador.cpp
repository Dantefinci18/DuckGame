#include "server_aceptador.h"

#include <sstream>
#include <string>
#include <tuple>
#include <utility>

#include "../common/common_liberror.h"

Aceptador::Aceptador(Socket& skt):skt(skt) {}

void Aceptador::run() {
    gameloop.start();
    while (_keep_running) {
        try {

            Socket conexion = skt.accept();
            gameloop.eliminar_desconectados();
            gameloop.agregar_jugador(conexion);

        } catch (const LibError& e) {}
    }

    gameloop.cerrar_conexiones();
    gameloop.stop();
    gameloop.join();
}