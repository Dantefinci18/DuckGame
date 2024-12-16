#ifndef SERVER_MONITOR_H
#define SERVER_MONITOR_H

#include <list>
#include <mutex>
#include <string>
#include <unordered_map>
#include "../common/common_queue.h"
#include "../common/common_evento.h"
#include "Vector.h"

class PlayerMonitor {
    private:
        std::list<Queue<std::unique_ptr<Evento>>*> colas_de_eventos;
        std::mutex mtx;

    public:
        void agregar_cola_evento(Queue<std::unique_ptr<Evento>>& cola_evento);
        void eliminar_cola_evento(Queue<std::unique_ptr<Evento>>& cola_evento);
        void enviar_evento(const Evento& evento);
};

#endif
