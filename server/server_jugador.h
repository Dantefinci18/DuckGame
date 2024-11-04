#ifndef SERVER_JUGADOR_H
#define SERVER_JUGADOR_H

#include <string>
#include <tuple>
#include <random>
#include <cstdint>
#include "../common/common_socket.h"
#include "server_receiver.h"
#include "server_sender.h"
#include "Player.h"

class Jugador {
private:
    ProtocoloServidor protocolo;
    Queue<Evento> cola_eventos;
    int id;
    Sender sender;
    Receiver receiver;
    Player playerPhysics;
    int generar_id();

public:
    explicit Jugador(Queue<Accion> &comandos, Socket&& conexion);

    void run();

    void stop();

    bool esta_conectado();

    void enviar_evento(Evento evento);

    void cerrar_conexion();

    int get_id();
    Player* get_fisicas();
    void update_fisicas(std::vector<Collidable*> collidables);
};

#endif
