#include "server_gameloop.h"
#include "../common/common_evento.h"
#include "../common/common_color.h"
#include "DisparoManager.h"

Gameloop::Gameloop(int id_jugador, unsigned int capacidad_minima, Queue<std::unique_ptr<Evento>>& cola_eventos)
    : capacidad_minima(capacidad_minima), 
    mapa(std::make_unique<Mapa>(1)), 
    color(0), 
    ticks_round_win_screen(60), 
    should_reset_round(false), 
    leaderboard() {
    
    agregar_jugador(id_jugador,cola_eventos);
}

void Gameloop::agregar_jugador(int id_jugador, Queue<std::unique_ptr<Evento>>& cola_eventos) {

    monitor.agregar_cola_evento(cola_eventos);
    ColorDuck color_asignado = static_cast<ColorDuck>(color % static_cast<int>(ColorDuck::MAX_COLOR));
    std::shared_ptr<Player> jugador = std::make_shared<Player>(id_jugador,color_asignado);

    jugadores[id_jugador] = jugador;
    leaderboard.add_player_id(jugador->get_id());
    cantidad_de_jugadores++;
    color++;
}

void Gameloop::run() {

    EventoMapa eventoMapa(mapa->getCollidables(), leaderboard);
    monitor.enviar_evento(eventoMapa);
    
    while (_keep_running) {
        cargar_acciones();
        sleep();
    }
}

void Gameloop::procesar_acciones(std::vector<Accion> acciones, std::vector<Collidable*> collidables) {
    std::vector<std::shared_ptr<Evento>> eventos;

    for (auto& accion : acciones) {
        std::lock_guard<std::mutex> lock(mtx);

        int id = accion.get_player_id();
        ComandoAccion command = accion.get_command();
        std::shared_ptr<Player> player = jugadores[id];
        if (player->is_duck_dead()) {
            continue;
        }

        if (command == DERECHA) {
            player->set_x_direction(1.0f);
        } else if (command == IZQUIERDA) {
            player->set_x_direction(-1.0f);
        } else if (command == SALTAR) {
            player->jump();
        } else if (command == QUIETO) {
            player->set_x_direction(0.0f);
        
        } else if (command == DISPARAR){
            player->iniciar_disparo();
            /*std::vector<std::shared_ptr<Evento>> eventos;
            if(player->has_weapon()){
                DisparoManager::procesar_disparo(*player, collidables, jugadores);
            }*/
        } else if (command == DEJAR_DISPARAR){
            player->dejar_disparar();
        } else if (command == RECARGAR) {
            player->reload();
        } else if (command == APUNTAR_ARRIBA) {
            player->apuntar_arriba();
        } else if (command == DEJAR_APUNTAR_ARRIBA) {
            player->dejar_apuntar_arriba();
        } else if (command == AGACHARSE) {
            std::cout << "agacharse" << std::endl;
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

    

    for (auto& player : jugadores) {
        player.second->update(collidables);

        if(player.second->esta_disparando()){
            std::vector<Collidable*> collidables_a_agregar;
            DisparoManager::procesar_disparo(*player.second, collidables, jugadores, balas,eventos, collidables_a_agregar);
            mapa->agregar_collidables(collidables_a_agregar);
        }

        for (auto& evento : player.second->eventos) {
            monitor.enviar_evento(*evento);
        }
        player.second->eventos.clear();
    }

    for (auto& evento : eventos) {
        monitor.enviar_evento(*evento);
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
            mapa = std::make_unique<Mapa>(getRandomMapIndex());
            ticks_round_win_screen = 60;
            should_reset_round = false;
            EventoMapa eventoMapa(mapa->getCollidables(), leaderboard);
            monitor.enviar_evento(eventoMapa);
        }
        return;
    }

    Player* winner = get_winner();
    if (winner) {
        handle_winner(winner);
        return;
    }
    procesar_acciones(acciones, mapa->getCollidables());
}

void Gameloop::reset_jugadores() {
    for (auto& player : jugadores) {
        player.second->reset();
        for (auto& evento : player.second->eventos) {
            monitor.enviar_evento(*evento);
        }
        player.second->eventos.clear();
    }
}

Player* Gameloop::get_winner() {
    Player* winner = nullptr;
    int alive_count = 0;

    for (auto& pair : jugadores) {
        Player* player = pair.second.get();
        if (!player->is_duck_dead()) {
            ++alive_count;
            if (alive_count > 1) {
                return nullptr; // More than one player alive, no winner yet.
            }
            winner = pair.second.get();
        }
    }
    return (alive_count == 1) ? winner : nullptr;
}

void Gameloop::handle_winner(Player* winner) {
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


Queue<Accion>& Gameloop::get_cola_acciones(){
    return comandos_acciones;
}

void Gameloop::sleep() {
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
}

std::vector<int> Gameloop::get_ids(){
    std::vector<int> ids_jugadores;

    for(auto pair : jugadores){
        ids_jugadores.push_back(pair.first);
    }

    return ids_jugadores;
}

void Gameloop::eliminar_jugador(int id_jugador,Queue<std::unique_ptr<Evento>>& cola_eventos){
    monitor.eliminar_cola_evento(cola_eventos);
    jugadores.erase(id_jugador);
}

bool Gameloop::esta_llena(){
    return cantidad_de_jugadores == capacidad_minima;
}

bool Gameloop::esta_vacia(){
    return cantidad_de_jugadores == 0;
}

int Gameloop::getRandomMapIndex() {
    std::vector<fs::directory_entry> files;

    for (const auto& entry : fs::directory_iterator("../server/mapas")) {
        if (fs::is_regular_file(entry)) { 
            files.push_back(entry);
        }
    }

    size_t numFiles = files.size();
    if (numFiles == 0) {
        std::cerr << "No files in the directory." << std::endl;
        return -1;
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, numFiles - 1);

    return dist(gen) + 1; 
}
