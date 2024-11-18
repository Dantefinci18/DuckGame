#include "server_gameloop.h"

#include "../common/common_evento.h"


Gameloop::Gameloop(Queue<Accion> &comandos_acciones, PlayerMonitor& monitor):
 comandos_acciones(comandos_acciones), monitor(monitor), mapa(1) {}

void Gameloop::run() {
    while (_keep_running) {
        procesar_acciones();
        sleep();
    }
}

void Gameloop::procesar_acciones() {
    std::vector<Accion> acciones;
    Accion accion;
    bool tried = comandos_acciones.try_pop(accion);
    while (tried) {
        acciones.push_back(accion);
        tried = comandos_acciones.try_pop(accion);
    }
    monitor.procesar_acciones(acciones, mapa.getCollidables());
}

void Gameloop::sleep() { std::this_thread::sleep_for(std::chrono::milliseconds(50)); }