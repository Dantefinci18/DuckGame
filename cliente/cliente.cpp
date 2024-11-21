
#include "cliente.h"
#include "../common/common_evento.h"
#include "../common/common_queue.h"
#include "../common/common_weapon_utils.h"
#include "enemigo.h"
#include <iostream>
#include <memory>
#include "../server/Platform.h"  

Cliente::Cliente(int id,Socket&& socket, std::vector<Collidable*> collidables, float x_inicial, float y_inicial)
    : id(id),
      window(800,600),
      duck(window, x_inicial,y_inicial),
      mapa(window, "../Imagenes/forest.png", collidables),
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
                    if (evento_mov->direccion_apuntada == DireccionApuntada::APUNTADO_ARRIBA) {
                        std::cout << "APUNTA PARA ARRIBA" << std::endl;
                    } else if (evento_mov->direccion_apuntada == DireccionApuntada::APUNTADO_DERECHA) {
                        std::cout << "APUNTA A LA DERECHA" << std::endl;
                    } else if (evento_mov->direccion_apuntada == DireccionApuntada::APUNTADO_IZQUIERDA) {
                        std::cout << "APUNTA A LA IZQUIERDA" << std::endl;
                    }
                    manejar_enemigos(*evento_mov, collidables);  
                    break;
                }
                case Evento::EventoMapa: {

                    break;
                }

                case Evento::EventoDisparo: {
                    auto evento_disparo = static_cast<EventoDisparo*>(evento_recibido.get());
                    break;
                }

                case Evento::EventoMuerte: {
                    auto evento_muerte = static_cast<EventoMuerte*>(evento_recibido.get());
                    manejar_muerte(*evento_muerte);
                    break;
                }

                case Evento::EventoPickup: {
                    auto evento_pickup = static_cast<EventoPickup*>(evento_recibido.get());
                    manejar_arma(*evento_pickup, collidables);
                    break;
                }

                case Evento::EventoSpawnArma: {
                    auto evento_spawn_arma = static_cast<EventoSpawnArma*>(evento_recibido.get());
                    spawn_arma(*evento_spawn_arma, collidables);
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
                evento_mov.id, evento_mov.x, evento_mov.y, window);
        }
    } else {
        duck.mover_a(evento_mov.x, evento_mov.y);
    }
}

void Cliente::manejar_arma(const EventoPickup& evento_pickup, std::vector<Collidable*> collidables) {
    for (auto& collidable : collidables) {
        if (collidable->getType() == CollidableType::SpawnPlace 
            && collidable->position.x == evento_pickup.x
            && collidable->position.y == evento_pickup.y) {
            SpawnPlace* sPlace = static_cast<SpawnPlace*>(collidable);
            sPlace->clear_weapon();
        }
    }
    if (evento_pickup.id != id) {
        auto it = enemigos.find(evento_pickup.id);
        if (it != enemigos.end()) {
            it->second->set_weapon(evento_pickup.weapon_type);
            return;
        }
    }
    duck.set_weapon(evento_pickup.weapon_type);
}

void Cliente::manejar_muerte(const EventoMuerte& evento_muerte) {
    if (evento_muerte.id != id) {
        auto it = enemigos.find(evento_muerte.id);
        if (it != enemigos.end()) {
            it->second->kill();
            return;
        }
    }
    duck.kill();
}

void Cliente::spawn_arma(const EventoSpawnArma& evento_spawn, std::vector<Collidable*> collidables) {
    for (auto& collidable : collidables) {
        if (collidable->getType() == CollidableType::SpawnPlace 
            && collidable->position.x == evento_spawn.x
            && collidable->position.y == evento_spawn.y) {
            SpawnPlace* sPlace = static_cast<SpawnPlace*>(collidable);
            sPlace->set_weapon(WeaponUtils::create_weapon(evento_spawn.weapon_type));
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
                } else if (evento.key.keysym.sym == SDLK_v) {
                    enviar_accion(tecla_anterior, DISPARAR);
                } else if (evento.key.keysym.sym == SDLK_r) {
                    enviar_accion(tecla_anterior, RECARGAR);
                } else if (evento.key.keysym.sym == SDLK_UP) {
                    enviar_accion(tecla_anterior, APUNTAR_ARRIBA);
                }
                break;
            case SDL_KEYUP:
                if (evento.key.keysym.sym == SDLK_LEFT || evento.key.keysym.sym == SDLK_RIGHT) {
                    enviar_accion(tecla_anterior, QUIETO);
                } else if (evento.key.keysym.sym == SDLK_SPACE) {
                    *tecla_anterior = ComandoAccion::QUIETO;
                } else if (evento.key.keysym.sym == SDLK_v) {
                    enviar_accion(tecla_anterior, DEJAR_DISPARAR);
                } else if (evento.key.keysym.sym == SDLK_UP) {
                    enviar_accion(tecla_anterior, DEJAR_APUNTAR_ARRIBA);
                }
                break;
        }
    }
}


void Cliente::ejecutar_juego() {
    
    const int frameDelay = 50;  
    Uint32 lastRenderTime = SDL_GetTicks();

    ComandoAccion tecla_anterior = QUIETO;

    while (conectado) {
        Uint32 currentTime = SDL_GetTicks();

        if (currentTime - lastRenderTime >= frameDelay) {
            lastRenderTime = currentTime;

            mapa.render();

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