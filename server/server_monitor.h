#ifndef SERVER_MONITOR_H
#define SERVER_MONITOR_H

#include <list>
#include <mutex>
#include <string>

#include "common_queue.h"
#include "../common/estado.h"

class Monitor {
private:
    std::list<Queue<Estado>*> queues_de_estados;
    std::mutex mtx;

public:
    void agregar_queue(Queue<Estado>& queue);

    void eliminar_queue(Queue<Estado>& queue);

    void enviar_estado(const Estado& estado);
};

#endif
