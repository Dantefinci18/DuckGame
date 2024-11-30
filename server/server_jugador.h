#ifndef SERVER_JUGADOR_H
#define SERVER_JUGADOR_H

#include <string>
#include <tuple>
#include <random>
#include <cstdint>
#include <mutex>
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
    Queue<std::unique_ptr<Evento>> cola_eventos;
    Sender sender;
    std::mutex mtx;
    Receiver receiver;
    int generar_id();

public:
    explicit Jugador(Queue<Accion> &comandos,Socket&& conexion);

    void run();

    void stop();

    bool esta_conectado();

    void cerrar_conexion();

    int get_id();

    void reset(Queue<Accion> &comandos);

    Queue<std::unique_ptr<Evento>>& get_cola_eventos();

    void enviar_evento(const Evento& evento);
};

#endif
