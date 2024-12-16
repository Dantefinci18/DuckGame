#include "server_monitor.h"
#include "DisparoManager.h"

#include <iostream>
#include <string>

void PlayerMonitor::agregar_cola_evento(Queue<std::unique_ptr<Evento>>& cola_evento) {
    std::lock_guard<std::mutex> lock(mtx);
    colas_de_eventos.push_back(&cola_evento);
}
void PlayerMonitor::eliminar_cola_evento(Queue<std::unique_ptr<Evento>>& cola_evento) {
    std::lock_guard<std::mutex> lock(mtx);
    colas_de_eventos.remove(&cola_evento);
}

void PlayerMonitor::enviar_evento(const Evento& evento) {
    std::lock_guard<std::mutex> lock(mtx);
    for (auto cola : colas_de_eventos) {
        std::unique_ptr<Evento> evento_ptr = evento.clone();
        cola->push(std::move(evento_ptr));
    }
}
