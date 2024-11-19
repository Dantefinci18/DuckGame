#ifndef SERVER_JUGADOR_H
#define SERVER_JUGADOR_H

#include <string>
#include <tuple>
#include <random>
#include <cstdint>
#include "../common/common_socket.h"
#include "../common/common_color.h"
#include "../common/common_queue.h"
#include "../common/common_color.h"

#include "server_receiver.h"
#include "server_sender.h"
#include "server_monitor.h"
#include "Player.h"

class Jugador {
private:
    ProtocoloServidor protocolo;
    int id;
    Sender sender;
    Receiver receiver;
    Player playerPhysics;
    int generar_id();

public:
    explicit Jugador(Queue<Accion> &comandos,PlayerMonitor& monitor ,Socket&& conexion, ColorDuck color);

    void run();

    void stop();

    bool esta_conectado();

    void cerrar_conexion();

    int get_id();
    Player* get_fisicas();
    void update_fisicas(std::vector<Collidable*> collidables);


    ~Jugador();
};

#endif
