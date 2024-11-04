#define ANCHO_VENTANA 800
#define ALTO_VENTANA 600

#include "cliente.h"

#include "../common/common_evento.h"
#include "../common/common_queue.h"

Cliente::Cliente(const char* hostname, const char* servname):
        window(ANCHO_VENTANA,ALTO_VENTANA),
        duck(window,300.0f, 200.0f),
        protocolo(hostname, servname),
        receiver(protocolo, queue_eventos, conectado),
        sender(protocolo, queue_acciones) {}

void Cliente::start() {
    receiver.start();
    sender.start();
    ejecutar_juego();
    stop();
    join();
}

void Cliente::procesar_eventos_recibidos() {
    Evento evento_recibido;
    bool tried = true;
    
    while (tried) {
        tried = queue_eventos.try_pop(evento_recibido);
        if (tried) {
            duck.mover_a_una_posicion(evento_recibido.x,evento_recibido.y);
        }
    }

}

void Cliente::enviar_accion(ComandoAccion *tecla_anterior, ComandoAccion accion){
     if (*tecla_anterior != accion && conectado) {
        queue_acciones.push(accion);
        *tecla_anterior = accion;    
    }
}

void Cliente::controlar_eventos_del_teclado(ComandoAccion* tecla_anterior){
    SDL_Event evento;
    if (SDL_PollEvent(&evento)) {
        switch (evento.type) {
            case SDL_QUIT:
                conectado = false;
                break;

            case SDL_KEYDOWN:
                if (evento.key.keysym.sym == SDLK_LEFT) {
                    enviar_accion(tecla_anterior,IZQUIERDA);
                
                } else if (evento.key.keysym.sym == SDLK_RIGHT) {
                    enviar_accion(tecla_anterior,DERECHA);

                } else if (evento.key.keysym.sym == SDLK_SPACE) {
                    enviar_accion(tecla_anterior,SALTAR);
                }
                break;

            case SDL_KEYUP:
                if (evento.key.keysym.sym == SDLK_LEFT || evento.key.keysym.sym == SDLK_RIGHT) {
                    enviar_accion(tecla_anterior,QUIETO);
                }
                if (evento.key.keysym.sym == SDLK_SPACE) {
                    *tecla_anterior = ComandoAccion::QUIETO;
                }
                break;

        }
    }
}

void Cliente::ejecutar_juego() {
    window.set_title("DuckGame");
    SdlTexture fondo("../Imagenes/Fondo.png", window);
    Area srcArea(0, 0, ANCHO_VENTANA, ALTO_VENTANA);
    Area destArea(0, 0, ANCHO_VENTANA, ALTO_VENTANA);
    fondo.render(srcArea, destArea, SDL_FLIP_NONE);
    duck.start();  
    const int frameDelay = 1000 / 15; // 15 FPS para renderizado
    Uint32 lastRenderTime = SDL_GetTicks();

    ComandoAccion tecla_anterior = QUIETO;

    while (conectado) {
        Uint32 currentTime = SDL_GetTicks();

        // Renderiza la animación y la escena cada 15 FPS
        if (currentTime - lastRenderTime >= frameDelay) {
            lastRenderTime = currentTime;

            fondo.render(srcArea, destArea, SDL_FLIP_NONE);
            duck.render();
            window.render();
        }

        // Procesa eventos recibidos y eventos de teclado sin bloquear
        procesar_eventos_recibidos();
        controlar_eventos_del_teclado(&tecla_anterior);

        // Pausa breve para reducir el uso de CPU
        SDL_Delay(1);
    }
}


void Cliente::stop() {
    receiver.stop();
    sender.stop();
    duck.stop();
    protocolo.cerrar_conexion();
    queue_eventos.close();
    queue_acciones.close();
}

void Cliente::join() {
    duck.join();
    receiver.join();
    sender.join();
}
