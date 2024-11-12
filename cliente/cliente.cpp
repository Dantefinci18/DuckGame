#define ANCHO_VENTANA 800
#define ALTO_VENTANA 600
#include "cliente.h"
#include "../common/common_evento.h"
#include "../common/common_queue.h"
#include "enemigo.h"  

Cliente::Cliente(Socket&& socket)
    : window(ANCHO_VENTANA, ALTO_VENTANA),
      duck(window, 200.0f, 300.0f),
      protocolo(std::move(socket)),
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
    std::unique_ptr<Evento> evento_recibido;
    bool tried = true;

    while (tried) {
        tried = queue_eventos.try_pop(evento_recibido);
        if (tried && evento_recibido) {
            switch (evento_recibido->get_tipo()) {
                case Evento::EventoMovimiento: {
                    auto evento_mov = static_cast<EventoMovimiento*>(evento_recibido.get());
                    std::cout << evento_mov->id << std::endl;
                    manejar_enemigos(*evento_mov);  
                    break;
                }
                case Evento::EventoMapa: {
                    auto evento_mapa = static_cast<EventoMapa*>(evento_recibido.get());
                    break;
                }
                default:
                    std::cerr << "Error: Tipo de evento desconocido" << std::endl;
                    break;
            }
        }
    }
}
void Cliente::manejar_enemigos(const EventoMovimiento& evento_mov) {
    if (evento_mov.id != id) {
        auto it = enemigos.find(evento_mov.id);
        if (it != enemigos.end()) {
            it->second->mover_a(evento_mov.x, evento_mov.y);
        } else {
            enemigos[evento_mov.id] = std::make_unique<Enemigo>(
                evento_mov.id, evento_mov.x, evento_mov.y, window);
        }
    } else {
        duck.mover_a_una_posicion(evento_mov.x, evento_mov.y);
    }
}


void Cliente::enviar_accion(ComandoAccion* tecla_anterior, ComandoAccion accion) {
    if (*tecla_anterior != accion && conectado) {
        queue_acciones.push(std::move(accion));

        *tecla_anterior = accion;
    }
}

void Cliente::controlar_eventos_del_teclado(ComandoAccion* tecla_anterior) {
    SDL_Event evento;
    if (SDL_PollEvent(&evento)) {
        switch (evento.type) {
            case SDL_QUIT:
                conectado = false;
                break;

            case SDL_KEYDOWN:
                if (evento.key.keysym.sym == SDLK_LEFT) {
                    enviar_accion(tecla_anterior, IZQUIERDA);
                } else if (evento.key.keysym.sym == SDLK_RIGHT) {
                    enviar_accion(tecla_anterior, DERECHA);
                } else if (evento.key.keysym.sym == SDLK_SPACE) {
                    enviar_accion(tecla_anterior, SALTAR);
                }
                break;

            case SDL_KEYUP:
                if (evento.key.keysym.sym == SDLK_LEFT || evento.key.keysym.sym == SDLK_RIGHT) {
                    enviar_accion(tecla_anterior, QUIETO);
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
    const int frameDelay = 100;  
    Uint32 lastRenderTime = SDL_GetTicks();

    ComandoAccion tecla_anterior = QUIETO;

    while (conectado) {
        Uint32 currentTime = SDL_GetTicks();

        if (currentTime - lastRenderTime >= frameDelay) {
            lastRenderTime = currentTime;

            fondo.render(srcArea, destArea, SDL_FLIP_NONE);

            if (!duck.esta_quieto()) {
                duck.render();
            }

            for (auto& pair : enemigos) {
                pair.second->renderizar();  
            }

            window.render();
        }

        procesar_eventos_recibidos();
        controlar_eventos_del_teclado(&tecla_anterior);

        SDL_Delay(1);
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