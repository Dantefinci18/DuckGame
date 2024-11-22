#ifndef SERVER_GAMELOOP_H
#define SERVER_GAMELOOP_H

#include <list>
#include <mutex>
#include <string>
#include <tuple>
#include "DisparoManager.h"
#include "../common/common_queue.h"
#include "../common/common_thread.h"
#include "../common/common_accion.h"
#include "server_monitor.h"
#include "server_jugador.h"
#include "server_mapa.h"

enum EstadoGameloop{
    EN_ESPERA,
    COMENZADA,
    TERMINADA
};

class Gameloop: public Thread {
private:
    Queue<Accion> comandos_acciones;
    PlayerMonitor monitor;
    std::unordered_map<int, Jugador*> jugadores;
    EstadoGameloop estado = EN_ESPERA;
    unsigned int capacidad_minima;
    unsigned int cantidad_de_jugadores = 0;
    std::mutex mtx;
    Mapa mapa;
    int color;

    void sleep();
    void cargar_acciones();
    void procesar_acciones(std::vector<Accion> acciones, std::vector<Collidable*> collidables);
    void eliminar_jugador(std::unordered_map<int, Jugador*>::iterator it);
    void eliminar_desconectados();

public:
    explicit Gameloop(Socket& skt,unsigned int capacidad_minima);

    void agregar_jugador(Socket& skt);
    void run() override;
    EstadoGameloop get_estado();
    void cerrar_conexiones();
};

#endif
