#ifndef SERVER_GAMELOOP_H
#define SERVER_GAMELOOP_H

#include <list>
#include <mutex>
#include <string>
#include <tuple>

#include "../common/common_queue.h"
#include "../common/common_thread.h"
#include "../common/common_accion.h"
#include "server_monitor.h"
#include "server_jugador.h"
#include "server_mapa.h"

class Gameloop: public Thread {
private:
    Queue<Accion> comandos_acciones;
    PlayerMonitor monitor;
    std::unordered_map<int, Jugador*> jugadores;
    std::mutex mtx;
    Mapa mapa;

    void sleep();
    void cargar_acciones();
    void procesar_acciones(std::vector<Accion> acciones, std::vector<Collidable*> collidables);
    void eliminar_jugador(std::unordered_map<int, Jugador*>::iterator& it);

public:
    explicit Gameloop();

    void agregar_jugador(Socket& jugador);
    void eliminar_desconectados();
    void run() override;
    void cerrar_conexiones();
};

#endif
