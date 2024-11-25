#include "server_gameloop.h"
#include "../common/common_evento.h"
#include "../common/common_color.h"

Gameloop::Gameloop(Socket& skt, unsigned int capacidad_minima)
    : capacidad_minima(capacidad_minima), mapa(std::make_unique<Mapa>(1)), color(0), ticks_round_win_screen(60), should_reset_round(false), leaderboard() {
    agregar_jugador(skt);
    this->start();
}

void Gameloop::agregar_jugador(Socket& skt) {
    std::lock_guard<std::mutex> lock(mtx);

    ColorDuck color_asignado = static_cast<ColorDuck>(color % static_cast<int>(ColorDuck::MAX_COLOR));

    if (color_asignado == ColorDuck::MAX_COLOR) {
        std::cout << "MAX_COLOR\n";
    }

    Jugador* jugador = new Jugador(comandos_acciones, monitor, std::move(skt), color_asignado);

    jugador->run();
    jugadores[jugador->get_id()] = jugador;
    leaderboard.add_player_id(jugador->get_id());
    cantidad_de_jugadores++;
    color++;

    if (cantidad_de_jugadores == capacidad_minima) {
        estado = COMENZADA;
        EventoMapa eventoMapa(mapa->getCollidables(), leaderboard);
        monitor.enviar_evento(eventoMapa);
    } else {
        monitor.enviar_evento(EventoEspera());
    }
}

void Gameloop::eliminar_jugador(std::unordered_map<int, Jugador*>::iterator it) {
    it->second->stop();
    delete it->second;
    cantidad_de_jugadores--;
}

void Gameloop::eliminar_desconectados() {
    std::lock_guard<std::mutex> lock(mtx);

    for (auto it = jugadores.begin(); it != jugadores.end();) {
        if (!it->second->esta_conectado()) {
            it->second->stop();
            delete it->second;
            it = jugadores.erase(it);
            cantidad_de_jugadores--;
        } else {
            ++it;
        }
    }
}

EstadoGameloop Gameloop::get_estado() {
    return estado;
}

void Gameloop::run() {
    while (_keep_running) {
        eliminar_desconectados();

        if (estado == COMENZADA) {
            if (cantidad_de_jugadores < capacidad_minima) {
                _keep_running = false;
            } else {
                cargar_acciones();
                sleep();
            }

        } else if (estado == EN_ESPERA && cantidad_de_jugadores == 0) {
            _keep_running = false;
        }
    }

    estado = TERMINADA;
    cerrar_conexiones();
}

void Gameloop::procesar_acciones(std::vector<Accion> acciones, std::vector<Collidable*> collidables) {
    std::vector<std::shared_ptr<Evento>> eventos;

    for (auto& accion : acciones) {
        std::lock_guard<std::mutex> lock(mtx);

        int id = accion.get_player_id();
        ComandoAccion command = accion.get_command();
        Player* player = jugadores[id]->get_fisicas();
        if (player->is_duck_dead()) {
            continue;
        }

        if (command == DERECHA) {
            player->set_x_direction(1.0f);
        } else if (command == IZQUIERDA) {
            player->set_x_direction(-1.0f);
        } else if (command == SALTAR) {
            std::cout << "jumps" << std::endl;
            player->jump();
        } else if (command == QUIETO) {
            player->set_x_direction(0.0f);
        } else if (command == DISPARAR) {
            if (player->has_weapon()) {
                std::vector<Collidable*> collidables_a_agregar;
                DisparoManager::procesar_disparo(*player, collidables, jugadores, balas,eventos, collidables_a_agregar);
                mapa->agregar_collidables(collidables_a_agregar);
            }
        } else if (command == DEJAR_DISPARAR) {
            std::cout << "Dejo de disparar" << std::endl;
            player->dejar_disparar();
        } else if (command == RECARGAR) {
            player->reload();
        } else if (command == APUNTAR_ARRIBA) {
            player->apuntar_arriba();
        } else if (command == DEJAR_APUNTAR_ARRIBA) {
            player->dejar_apuntar_arriba();
        } else if (command == AGACHARSE) {
            player->agacharse();
        } else if (command == LEVANTARSE) {
            player->levantarse();
        }
    }

    for (auto& collidable : collidables) {
        collidable->update(collidables);

        if (collidable->getType() == CollidableType::SpawnPlace) {
            SpawnPlace& sPlace = static_cast<SpawnPlace&>(*collidable);
            for (auto& evento : sPlace.eventos) {
                std::cout << "hereeee" << std::endl;
                monitor.enviar_evento(*evento);
            }
            sPlace.eventos.clear();
        }
    }

    std::lock_guard<std::mutex> lock(mtx);

    for (auto& bala : balas) {
        while (bala.actualizar(0.3f)) {
            
            EventoBala eventoBala(bala.getX(), bala.getY());
            monitor.enviar_evento(eventoBala);
        }
    }

    for (auto& evento : eventos) {
        monitor.enviar_evento(*evento);
    }

    for (auto& player : jugadores) {
        player.second->update_fisicas(collidables);

        for (auto& evento : player.second->get_fisicas()->eventos) {
            monitor.enviar_evento(*evento);
        }
        player.second->get_fisicas()->eventos.clear();
    }
}

void Gameloop::cargar_acciones() {
    std::vector<Accion> acciones;
    Accion accion;
    bool tried = comandos_acciones.try_pop(accion);

    while (tried) {
        acciones.push_back(accion);
        tried = comandos_acciones.try_pop(accion);
    }

    if (should_reset_round) {
        --ticks_round_win_screen;
        if (ticks_round_win_screen == 0) {
            std::cout << "reseting!" << std::endl;
            mapa = std::make_unique<Mapa>(3);
            ticks_round_win_screen = 60;
            should_reset_round = false;
            EventoMapa eventoMapa(mapa->getCollidables(), leaderboard);
            monitor.enviar_evento(eventoMapa);
        }
        return;
    }

    Jugador* winner = get_winner();
    if (winner) {
        handle_winner(winner);
        return;
    }
    procesar_acciones(acciones, mapa->getCollidables());
}

void Gameloop::reset_jugadores() {
    for (auto& player : jugadores) {
        player.second->get_fisicas()->reset();
        for (auto& evento : player.second->get_fisicas()->eventos) {
            monitor.enviar_evento(*evento);
        }
        player.second->get_fisicas()->eventos.clear();
    }
}

Jugador* Gameloop::get_winner() {
    Jugador* winner = nullptr;
    int alive_count = 0;

    for (auto& pair : jugadores) {
        Player* player = pair.second->get_fisicas();
        if (!player->is_duck_dead()) {
            ++alive_count;
            if (alive_count > 1) {
                return nullptr; // More than one player alive, no winner yet.
            }
            winner = pair.second;
        }
    }
    return (alive_count == 1) ? winner : nullptr;
}

void Gameloop::handle_winner(Jugador* winner) {
    should_reset_round = true;
    leaderboard.win_round(winner->get_id());
    int match_winner = leaderboard.get_match_winner();
    if (match_winner != 0) {
        EventoWinMatch eventoWinMatch(match_winner);
        monitor.enviar_evento(eventoWinMatch);
        _keep_running = false;
        return;
    }
    EventoWinRound eventoWinRound(winner->get_id());
    monitor.enviar_evento(eventoWinRound);
    reset_jugadores();
    return;
}

void Gameloop::sleep() {
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
}

void Gameloop::cerrar_conexiones() {
    for (auto it = jugadores.begin(); it != jugadores.end();) {
        eliminar_jugador(it);
        ++it;
    }
}
