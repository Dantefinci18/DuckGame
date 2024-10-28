#ifndef SERVER_SERVIDOR_H
#define SERVER_SERVIDOR_H

#include <string>
#include <tuple>

#include "common_queue.h"
#include "common_thread.h"
#include "server_aceptador.h"
#include "server_gameloop.h"
#include "server_monitor.h"

class Servidor {
private:
    Socket skt;
    //Queue<> eventos;
    Monitor monitor;
    Aceptador aceptador;
    Gameloop gameloop;

public:
    explicit Servidor(const char* nombre_servidor);

    void run();
};

#endif
