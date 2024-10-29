#ifndef SERVER_MONITOR_H
#define SERVER_MONITOR_H

#include <list>
#include <mutex>
#include <string>

#include "../common/common_queue.h"
#include "../common/estado.h"
#include "Vector.h"

class Monitor {
private:
    std::list<Queue<Vector>*> queues_de_estados;
    std::mutex mtx;

public:
    void agregar_queue(Queue<Vector>& queue);

    void eliminar_queue(Queue<Vector>& queue);

    void enviar_estado(const Vector& estado);
};

#endif
