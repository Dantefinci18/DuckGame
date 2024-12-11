#ifndef CLIENTE_TECLADO_H
#define CLIENTE_TECLADO_H

#include <atomic>
#include <SDL2/SDL.h>
#include "../common/common_thread.h"
#include "../common/common_accion.h"
#include "../common/common_queue.h"


class ClienteTeclado : public Thread {
private:
    std::atomic<bool>& conectado;
    Queue<ComandoAccion>& queue_acciones;
    ComandoAccion tecla_anterior;

    void enviar_accion(ComandoAccion* tecla_anterior, ComandoAccion accion);
    void procesar_evento(const SDL_Event& evento);

public:
    explicit ClienteTeclado(std::atomic<bool>& conectado,Queue<ComandoAccion>& queue_acciones);
    void run() override;
    void stop() override;
};

#endif // CLIENTE_TECLADO_H
