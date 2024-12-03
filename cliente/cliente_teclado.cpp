#include "cliente_teclado.h"

ClienteTeclado::ClienteTeclado(std::atomic<bool>& conectado,Queue<ComandoAccion>& queue_acciones)
    : conectado(conectado),queue_acciones(queue_acciones), tecla_anterior(ComandoAccion::QUIETO) {}

void ClienteTeclado::enviar_accion(ComandoAccion* tecla_anterior, ComandoAccion accion) {
    if (*tecla_anterior != accion) {
        queue_acciones.push(std::move(accion));
        *tecla_anterior = accion;
    }
}

void ClienteTeclado::procesar_evento(const SDL_Event& evento) {
    switch (evento.type) {
        case SDL_QUIT:
            conectado = false;
            break;

        case SDL_KEYDOWN:
            switch (evento.key.keysym.sym) {
                case SDLK_LEFT:
                    enviar_accion(&tecla_anterior, ComandoAccion::IZQUIERDA);
                    break;
                case SDLK_RIGHT:
                    enviar_accion(&tecla_anterior, ComandoAccion::DERECHA);
                    break;
                case SDLK_SPACE:
                    enviar_accion(&tecla_anterior, ComandoAccion::SALTAR);
                    break;
                case SDLK_v:
                    enviar_accion(&tecla_anterior, ComandoAccion::DISPARAR);
                    break;
                case SDLK_r:
                    enviar_accion(&tecla_anterior, ComandoAccion::RECARGAR);
                    break;
                case SDLK_UP:
                    enviar_accion(&tecla_anterior, ComandoAccion::APUNTAR_ARRIBA);
                    break;
                case SDLK_DOWN:
                    enviar_accion(&tecla_anterior, ComandoAccion::AGACHARSE);
                    break;
            }
            break;

        case SDL_KEYUP:
            switch (evento.key.keysym.sym) {
                case SDLK_LEFT:
                case SDLK_RIGHT:
                    enviar_accion(&tecla_anterior, ComandoAccion::QUIETO);
                    break;
                case SDLK_SPACE:
                    tecla_anterior = ComandoAccion::QUIETO;
                    break;
                case SDLK_v:
                    enviar_accion(&tecla_anterior, ComandoAccion::DEJAR_DISPARAR);
                    break;
                case SDLK_UP:
                    enviar_accion(&tecla_anterior, ComandoAccion::DEJAR_APUNTAR_ARRIBA);
                    break;
                case SDLK_DOWN:
                    enviar_accion(&tecla_anterior, ComandoAccion::LEVANTARSE);
                    break;
            }
            break;
    }
}

void ClienteTeclado::run() {
    SDL_Event evento;
    while (conectado) {
        if (SDL_WaitEvent(&evento)) {
            procesar_evento(evento);
        }
    }
}

void ClienteTeclado::stop() {
    conectado = false;
}
