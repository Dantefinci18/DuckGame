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
#include "server_mapa.h"

class Gameloop: public Thread {
private:
    Queue<Accion>& comandos_acciones;
    PlayerMonitor& monitor;
    std::mutex mtx;
    Mapa mapa;

    void sleep();
    void procesar_acciones();

public:
    explicit Gameloop(Queue<Accion>& comandos_acciones, PlayerMonitor& monitor);

    void run() override;
};

#endif
