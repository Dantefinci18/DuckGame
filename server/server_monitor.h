#ifndef SERVER_MONITOR_H
#define SERVER_MONITOR_H

#include <list>
#include <mutex>
#include <string>
#include <unordered_map>
#include "../common/common_queue.h"
#include "../common/common_evento.h"
#include "Vector.h"
#include "server_jugador.h"

class PlayerMonitor {
    private:
        std::unordered_map<int, Jugador*> jugadores;
        std::mutex mtx;

    public:
        void agregar_jugador(Jugador* jugador);
        void eliminar_jugador(int id);
        void broadcast_evento(const Evento& evento);
        Player* get_player(int id);
        
        void procesar_acciones(std::vector<Accion> acciones, std::vector<Collidable*> collidables);
};

#endif
