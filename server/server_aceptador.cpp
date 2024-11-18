#include "server_aceptador.h"

#include <sstream>
#include <string>
#include <tuple>
#include <utility>

#include "../common/common_liberror.h"

Aceptador::Aceptador(Queue<Accion>& comandos, PlayerMonitor& monitor, Socket& skt)
    : skt(skt), comandos(comandos), monitor(monitor), colorIndex(0) {}

void Aceptador::run() {
    while (_keep_running) {
        try {
            Socket conexion = skt.accept();

            ColorDuck color = static_cast<ColorDuck>(colorIndex);
            colorIndex = (colorIndex + 1) % 9; 

            auto jugador = new Jugador(comandos, std::move(conexion), color);
            jugador->run();

            jugadores.push_back(jugador);
            monitor.agregar_jugador(jugador);

        } catch (const LibError& e) {
        }
    }

    cerrar_conexiones();
}

void Aceptador::eliminar_jugador(Jugador* jugador) {
    jugadores.remove(jugador);
    jugador->stop();
    delete jugador;
}

void Aceptador::eliminar_desconectados() {
    for (auto it = jugadores.begin(); it != jugadores.end();) {
        Jugador* jugador = *it;
        if (!jugador->esta_conectado()) {
            it = jugadores.erase(it);
            eliminar_jugador(jugador);
        } else {
            ++it;
        }
    }
}

std::list<Jugador*> Aceptador::obtener_conectados() { return jugadores; }

void Aceptador::cerrar_conexiones() {
    for (auto jugador: jugadores) {
        jugador->cerrar_conexion();
        jugador->stop();
        delete jugador;
    }

    jugadores.clear();
}
