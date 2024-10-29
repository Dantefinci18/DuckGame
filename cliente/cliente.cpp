#include "cliente.h"

#include "../common/common_evento.h"
#include "../common/common_queue.h"

Cliente::Cliente(const char* hostname, const char* servname):
        protocolo(hostname, servname),
        receiver(protocolo, queue_eventos, conectado),
        sender(protocolo, queue_acciones) {}

void Cliente::start() {
    std::cout << "Cliente conectado" << std::endl;
    receiver.start();
    sender.start();
    bool esta_conectado = true;
    ingresar_accion(esta_conectado);
    stop();
    join();
}

void Cliente::ingresar_accion(bool &conectado) {  
    SDL_Event evento;
    std::string ultima_tecla_presionada;

    while (conectado) {

        Evento evento_recibido;
        if (queue_eventos.try_pop(evento_recibido)) {
            // procesar
        }

        while (SDL_PollEvent(&evento)) {
            switch (evento.type) {
                case SDL_QUIT:
                    conectado = false;
                    break;

                case SDL_KEYDOWN:
                    if (evento.key.keysym.sym == SDLK_LEFT) {
                        if (ultima_tecla_presionada != "izquierda") {
                            std::cout << "Se presionó la tecla izquierda" << std::endl;
                            queue_acciones.push(ComandoAccion::IZQUIERDA);
                            ultima_tecla_presionada = "izquierda";
                        }
                    } else if (evento.key.keysym.sym == SDLK_RIGHT) {
                        if (ultima_tecla_presionada != "derecha") {
                            std::cout << "Se presionó la tecla derecha" << std::endl;
                            queue_acciones.push(ComandoAccion::DERECHA);
                            ultima_tecla_presionada = "derecha";
                        }
                    } else if (evento.key.keysym.sym == SDLK_SPACE) {
                        std::cout << "Se presionó la tecla de salto" << std::endl;
                        queue_acciones.push(ComandoAccion::SALTAR);
                        ultima_tecla_presionada = "saltar";
                    }
                    break;

                case SDL_KEYUP:
                    if (evento.key.keysym.sym == SDLK_LEFT) {
                        std::cout << "Se soltó la tecla izquierda" << std::endl;
                        queue_acciones.push(ComandoAccion::STOP_IZQUIERDA);
                        if (ultima_tecla_presionada == "izquierda") {
                            ultima_tecla_presionada.clear();
                        }
                    } else if (evento.key.keysym.sym == SDLK_RIGHT) {
                        std::cout << "Se soltó la tecla derecha" << std::endl;
                        queue_acciones.push(ComandoAccion::STOP_DERECHA);
                        if (ultima_tecla_presionada == "derecha") {
                            ultima_tecla_presionada.clear();
                        }
                    }
                    break;
            }
        }
    }
}

void Cliente::stop() {
    receiver.stop();
    sender.stop();
    protocolo.cerrar_conexion();
    queue_eventos.close();
    queue_acciones.close();
}

void Cliente::join() {
    receiver.join();
    sender.join();
}
