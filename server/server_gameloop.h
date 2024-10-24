#ifndef SERVER_GAMELOOP_H
#define SERVER_GAMELOOP_H

#include <list>
#include <mutex>
#include <string>
#include <tuple>

#include "common_queue.h"
#include "common_thread.h"
#include "server_monitor.h"

class Gameloop: public Thread {
private:
    //Queue<>& eventos;
    //Juego juego;
    Monitor& monitor;
    std::mutex mtx;

    void ejecutar_eventos();

public:
    explicit Gameloop(/*Queue<>& eventos,*/ Monitor& monitor);

    void run() override;
};

#endif
