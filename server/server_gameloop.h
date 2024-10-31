#ifndef SERVER_GAMELOOP_H
#define SERVER_GAMELOOP_H

#include <list>
#include <mutex>
#include <string>
#include <tuple>

#include "../common/common_queue.h"
#include "../common/common_thread.h"
#include "../common/common_accion.h"
#include "Player.h"
#include "server_monitor.h"

class Gameloop: public Thread {
private:
    Queue<ComandoAccion>& comandos_acciones;
    Player player;
    Monitor& monitor;
    std::mutex mtx;

    void ejecutar_eventos();

public:
    explicit Gameloop(Queue<ComandoAccion> &comandos_acciones, Monitor& monitor);

    void run() override;
};

#endif
