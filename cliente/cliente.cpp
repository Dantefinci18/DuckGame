
#include "cliente.h"
#include "../common/common_evento.h"
#include "../common/common_queue.h"

#include "enemigo.h"
#include <iostream>
#include <memory>
#include "../server/Platform.h"  
#include "../server/SpawnWeaponBox.h"

Cliente::Cliente(int id,ColorDuck color,ClienteProtocolo& protocolo, std::vector<Collidable*> collidables, Leaderboard leaderboard, float x_inicial, float y_inicial): 
    id(id),
    window(800,600),
    duck(window, x_inicial,y_inicial, color),
    mapa(std::make_unique<Mapa>(window, "../Imagenes/forest.png", collidables)),
    leaderboard(ClientLeaderboard(window, leaderboard.round, leaderboard.max_rounds, leaderboard.set_of_rounds, leaderboard.player_rounds_won)),
    protocolo(std::move(protocolo)),
    receiver(protocolo, queue_eventos, conectado),
    sender(protocolo, queue_acciones),
    collidables(collidables),
    win_message(nullptr),
    should_end(nullptr) {}

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
            evento_recibido->print();
            switch (evento_recibido->get_tipo()) {
                case Evento::EventoMovimiento: {
                    auto evento_mov = static_cast<EventoMovimiento*>(evento_recibido.get());
                    manejar_enemigos(*evento_mov);  
                    break;
                }
                case Evento::EventoMapa: {
                    auto evento_mapa = static_cast<EventoMapa*>(evento_recibido.get());
                    mapa = std::make_unique<Mapa>(window, "../Imagenes/forest.png", evento_mapa->collidables);
                    collidables = evento_mapa->collidables;
                    leaderboard.update_map(evento_mapa->leaderboard.player_rounds_won);
                    leaderboard.update_round(evento_mapa->leaderboard.round);
                    leaderboard.update_set(evento_mapa->leaderboard.set_of_rounds);
                    win_message = nullptr;
                    break;
                }

                case Evento::EventoDisparo: {
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
                case Evento::EventoAgacharse: {
                    auto evento_agacharse = static_cast<EventoAgacharse*>(evento_recibido.get());
                    agachar_duck(*evento_agacharse);
                    break;
                }

                case Evento::EventoLevantarse: {
                    auto evento_levantarse = static_cast<EventoLevantarse*>(evento_recibido.get());
                    levantarse_duck(*evento_levantarse);
                    break;
                }
                case Evento::EventoWinRound: {
                    auto evento_win = static_cast<EventoWinRound*>(evento_recibido.get());
                    handle_win_screen(*evento_win);
                    break;
                }

                case Evento::EventoWinMatch: {
                    auto evento_win = static_cast<EventoWinMatch*>(evento_recibido.get());
                    handle_win_match_screen(*evento_win);
                    break;
                }   

                case Evento::EventoApuntar: {
                    auto evento_apuntar = static_cast<EventoApuntar*>(evento_recibido.get());
                    apuntar(*evento_apuntar);
                    break;
                }

                case Evento::EventoEspera: {
                    break;
                }

                case Evento::EventoBala: {
                    auto evento_bala = static_cast<EventoBala*>(evento_recibido.get());
                    disparar_bala(*evento_bala);
                    break;
                }

                case Evento::EventoCajaDestruida: {
                    auto evento_caja_destruida = static_cast<EventoCajaDestruida*>(evento_recibido.get());
                    eliminar_caja(*evento_caja_destruida);
                    break;
                }

                case Evento::EventoSpawnArmaBox: {
                    auto evento_spawn_arma_box = static_cast<EventoSpawnArmaBox*>(evento_recibido.get());
                    agregar_collidable(*evento_spawn_arma_box);

                    break;
                }
                default: {
                    std::cout << "Error: Tipo de evento desconocido" << std::endl;
                    break;
                }
            }
        }
    }
}

void Cliente::agregar_collidable(const EventoSpawnArmaBox& evento_spawn_arma_box) {
    auto* spawnWeaponBox = new SpawnWeaponBox(
        Vector(evento_spawn_arma_box.x, evento_spawn_arma_box.y), 
        20, 
        20
    );

    std::unique_ptr<Weapon> weapon = WeaponUtils::create_weapon(evento_spawn_arma_box.weapon_type);
    
    spawnWeaponBox->set_weapon(std::move(weapon));

    collidables.push_back(spawnWeaponBox);
    mapa->agregar_collidable(spawnWeaponBox);
}


void Cliente::eliminar_caja(const EventoCajaDestruida& evento_caja_destruida) {
    mapa->eliminar_caja(evento_caja_destruida.x, evento_caja_destruida.y);
}

void Cliente::disparar_bala(const EventoBala& evento_bala) {
    duck.setear_bala(evento_bala.x, evento_bala.y);
}

void Cliente::agachar_duck(const EventoAgacharse& evento_agacharse) {
    if (evento_agacharse.id != id) {
        auto it = enemigos.find(evento_agacharse.id);
        if (it != enemigos.end()) {
            it->second->agacharse();
        }
    } else {
        duck.agacharse();
    }
}

void Cliente::levantarse_duck(const EventoLevantarse& evento_levantarse) {
    if (evento_levantarse.id != id) {
        auto it = enemigos.find(evento_levantarse.id);
        if (it != enemigos.end()) {
            it->second->levantarse();
        }
    } else {
        duck.levantarse();
    }
}

void Cliente::manejar_enemigos(const EventoMovimiento& evento_mov) {
    if (evento_mov.id != id) {
        auto it = enemigos.find(evento_mov.id);
        if (it != enemigos.end()) {
            it->second->mover_a(evento_mov.x, evento_mov.y, evento_mov.is_flapping, evento_mov.reset);
            //This just sucks, change it
            leaderboard.set_color(evento_mov.color, evento_mov.id);
        } else {
            enemigos[evento_mov.id] = std::make_unique<Enemigo>(
                evento_mov.id, evento_mov.color, evento_mov.x, evento_mov.y, window);
            leaderboard.set_color(evento_mov.color, evento_mov.id);
        }
    } else {
        duck.mover_a(evento_mov.x, evento_mov.y, evento_mov.is_flapping, evento_mov.reset);
        leaderboard.set_color(evento_mov.color, evento_mov.id);
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
        if (collidable->getType() == CollidableType::SpawnWeaponBox 
            && collidable->position.x == evento_pickup.x
            && collidable->position.y == evento_pickup.y) {
            std::cout << "clearing weapon" << std::endl;
            SpawnWeaponBox* sWeaponBox = static_cast<SpawnWeaponBox*>(collidable);
            sWeaponBox->clear_weapon();
            mapa->clear_weapon(sWeaponBox);
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

void Cliente::apuntar(const EventoApuntar& evento_apuntar) {
    if (evento_apuntar.id == id) {
        duck.apuntar_arma(evento_apuntar.direccion);
    } else {
        auto it = enemigos.find(evento_apuntar.id);
        if (it != enemigos.end()) {
            it->second->apuntar_arma(evento_apuntar.direccion);
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
                } else if(evento.key.keysym.sym == SDLK_UP){
                    enviar_accion(tecla_anterior, APUNTAR_ARRIBA);
                } else if (evento.key.keysym.sym == SDLK_DOWN) {
                    enviar_accion(tecla_anterior,AGACHARSE);
                }
                break;

            case SDL_KEYUP:
                if (evento.key.keysym.sym == SDLK_LEFT || evento.key.keysym.sym == SDLK_RIGHT) {
                    enviar_accion(tecla_anterior, QUIETO);
                } else if (evento.key.keysym.sym == SDLK_SPACE) {
                    *tecla_anterior = ComandoAccion::QUIETO;
                } else if (evento.key.keysym.sym == SDLK_v) {
                    enviar_accion(tecla_anterior, DEJAR_DISPARAR);
                } else if (evento.key.keysym.sym == SDLK_UP){
                    enviar_accion(tecla_anterior, DEJAR_APUNTAR_ARRIBA);
                } else if (evento.key.keysym.sym == SDLK_DOWN) {
                    enviar_accion(tecla_anterior, LEVANTARSE);
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
            
            mapa->render();
            leaderboard.render();
            
            duck.render();
            if (win_message) {
                win_message->render();
               
            }
            for (auto& pair : enemigos) {
                pair.second->renderizar();  
            }
            window.render();
             if (should_end) {
                SDL_Delay(3000);
                conectado = false;
            }
        }

        procesar_eventos_recibidos();
        controlar_eventos_del_teclado(&tecla_anterior);

        SDL_Delay(1);
    }
}



void Cliente::handle_win_screen(const EventoWinRound& evento) {
    win_message = evento.id == id 
        ? std::make_unique<SdlFullscreenMessage>("Keep going!", window) 
        : std::make_unique<SdlFullscreenMessage>("Quack quack...\nBetter luck next time!", window);
}

void Cliente::handle_win_match_screen(const EventoWinMatch& evento) {
    win_message = evento.id == id 
        ? std::make_unique<SdlFullscreenMessage>("QUACK! YOU QUACKED THEM ALL!", window) 
        : std::make_unique<SdlFullscreenMessage>("They quacked you...", window);
    should_end = true;
}

std::unordered_map<ColorDuck, int> Cliente::get_colors(std::unordered_map<int,int> players_rounds) {
    std::unordered_map<ColorDuck, int> colors;
    for (auto& player : players_rounds) {
        if (player.first != id) {
            auto it = enemigos.find(player.first);
            if (it != enemigos.end()) {
                colors[it->second->get_color()] = player.second;
            } 
        } else {
            colors[duck.get_color()] = player.second;
        }
    }
    return colors;
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