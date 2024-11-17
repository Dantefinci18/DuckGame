#define ANCHO_VENTANA 800
#define ALTO_VENTANA 600
#include "cliente.h"
#include "../common/common_evento.h"
#include "../common/common_queue.h"
#include "enemigo.h"
#include <iostream>
#include <memory>
#include "../server/Platform.h"  

Cliente::Cliente(int id,Socket&& socket, std::vector<Collidable*> collidables, float x_inicial, float y_inicial)
    : id(id),
      window(ANCHO_VENTANA, ALTO_VENTANA),
      duck(window, x_inicial,y_inicial,collidables),
      protocolo(std::move(socket)),
      receiver(protocolo, queue_eventos, conectado),
      sender(protocolo, queue_acciones),
      collidables(collidables) {}

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
                    manejar_enemigos(*evento_mov, collidables);  
                    break;
                }
                case Evento::EventoMapa: {

                    break;
                }

                case Evento::EventoPickup: {
                    auto evento_pickup = static_cast<EventoPickup*>(evento_recibido.get());
                    manejar_arma(*evento_pickup, collidables);
                    break;
                }                
                default:
                    std::cout << "Error: Tipo de evento desconocido" << std::endl;
                    break;
            }
        }
    }
}
void Cliente::manejar_enemigos(const EventoMovimiento& evento_mov, std::vector<Collidable*> collidables) {
    if (evento_mov.id != id) {
        auto it = enemigos.find(evento_mov.id);
        if (it != enemigos.end()) {
            it->second->mover_a(evento_mov.x, evento_mov.y);
        } else {
            enemigos[evento_mov.id] = std::make_unique<Enemigo>(
                evento_mov.id, evento_mov.x, evento_mov.y, window, collidables);
        }
    } else {
        duck.mover_a_una_posicion(evento_mov.x, evento_mov.y);
    }
}

void Cliente::manejar_arma(const EventoPickup& evento_pickup, std::vector<Collidable*> collidables) {
    for (auto& collidable : collidables) {
        if (collidable->getType() == CollidableType::SpawnPlace 
            && collidable->position.x == evento_pickup.x
            && collidable->position.y == evento_pickup.y) {
            SpawnPlace& sPlace = static_cast<SpawnPlace&>(*collidable);
            sPlace.clear_weapon();
        }
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
    SdlTexture fondo("../Imagenes/forest.png", window);
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

            duck.render();

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

Cliente::~Cliente() {}