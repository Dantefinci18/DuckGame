#ifndef SERVER_ACEPTADOR_H
#define SERVER_ACEPTADOR_H

#include <list>
#include <string>
#include <tuple>

#include "../common/common_queue.h"
#include "../common/common_socket.h"
#include "../common/common_thread.h"
#include "../common/common_accion.h"
#include "server_jugador.h"
#include "server_monitor.h"

class Aceptador: public Thread {
private:
    Socket& skt;
    std::list<Jugador*> jugadores;
    Queue<ComandoAccion>& comandos;
    Monitor& monitor;

    void eliminar_desconectados();
    void cerrar_conexiones();

public:
    explicit Aceptador(Queue<ComandoAccion> &comandos, Monitor& monitor,
                       Socket& skt);

    void run() override;

    std::list<Jugador*> obtener_conectados();

    void eliminar_jugador(Jugador* jugador);
};

#endif
