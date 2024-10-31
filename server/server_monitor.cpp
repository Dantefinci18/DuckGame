#include "server_monitor.h"

#include <iostream>
#include <string>

void Monitor::agregar_queue(Queue<Vector>& queue) {
    std::lock_guard<std::mutex> lock(mtx);
    queues_de_estados.push_back(&queue);
}

void Monitor::eliminar_queue(Queue<Vector>& queue) {
    std::lock_guard<std::mutex> lock(mtx);
    queues_de_estados.remove(&queue);
}

void Monitor::enviar_estado(const Vector& posicion) {
    for (auto queue: queues_de_estados) {

        queue->push(posicion);
    }
}
