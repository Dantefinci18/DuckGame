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
        std::list<Queue<std::unique_ptr<Evento>>*> colas_de_eventos;
        std::mutex mtx;

    public:
        void agregar_cola_evento(Queue<std::unique_ptr<Evento>>& cola_evento);
        void eliminar_cola_evento(Queue<std::unique_ptr<Evento>>& cola_evento);
        std::unique_ptr<Evento>  broadcast_evento(const Evento& evento);
        void enviar_evento(const Evento& evento);
        Player* get_player(int id);
        
        void procesar_acciones(std::vector<Accion> acciones, std::vector<Collidable*> collidables);
};

#endif
