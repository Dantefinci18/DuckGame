#include "server_gameloop.h"

#include "../common/common_evento.h"
#include "../common/common_color.h"


Gameloop::Gameloop(Socket& skt,unsigned int capacidad_minima): 
    capacidad_minima(capacidad_minima), mapa(std::make_unique<Mapa>(1)), color(0), ticks_round_win_screen(60), should_reset_round(false){
        agregar_jugador(skt);
        this->start();
    }

void Gameloop::agregar_jugador(Socket& skt) {
    std::lock_guard<std::mutex> lock(mtx);

    ColorDuck color_asignado = static_cast<ColorDuck>(color % static_cast<int>(ColorDuck::MAX_COLOR));
    
    if(color_asignado == ColorDuck::MAX_COLOR){
        std::cout << "MAX_COLOR\n";
    }

    Jugador* jugador = new Jugador(comandos_acciones, monitor, std::move(skt), color_asignado);

    jugador->run();
    jugadores[jugador->get_id()] = jugador;

    cantidad_de_jugadores++;
    color++;
    
    if(cantidad_de_jugadores == capacidad_minima){
        estado = COMENZADA;
        EventoMapa eventoMapa(mapa->getCollidables());
        monitor.enviar_evento(eventoMapa);
    
    }else{
        monitor.enviar_evento(EventoEspera());
    }
}


    
void Gameloop::eliminar_jugador(std::unordered_map<int, Jugador*>::iterator it){
   it->second->stop();
   delete it->second;
   cantidad_de_jugadores--;
}

void Gameloop::eliminar_desconectados(){
    std::lock_guard<std::mutex> lock(mtx);

    for (auto it = jugadores.begin(); it != jugadores.end();) {        
        if (!it->second->esta_conectado()) {
            eliminar_jugador(it);
            it = jugadores.erase(it);
        
        } else {
            ++it;
        }
    }
}

EstadoGameloop Gameloop::get_estado(){
    return estado;
}

void Gameloop::run() {
    while (_keep_running) {
        eliminar_desconectados();

        if(estado == COMENZADA){
            if(cantidad_de_jugadores < capacidad_minima){
                _keep_running = false;
            
            } else {
                cargar_acciones();
                sleep();
            }
        
        }else if(estado == EN_ESPERA && cantidad_de_jugadores == 0){
            _keep_running = false;
        }
    }

    estado = TERMINADA;
    cerrar_conexiones();
}

void Gameloop::procesar_acciones(std::vector<Accion> acciones, std::vector<Collidable*> collidables){
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
        
        } else if (command == DISPARAR){
            std::vector<std::shared_ptr<Evento>> eventos;
            if(player->has_weapon()){
                DisparoManager::procesar_disparo(*player, collidables, jugadores);
            }
            /*
            for (const auto& evento : eventos) {
                std::cout << "manda un evento" <<std::endl;
                broadcast_evento(*evento);
            }*/
        } else if (command == DEJAR_DISPARAR){
            std::cout << "Dejo de disparar" << std::endl;
            player->dejar_disparar();
        } else if (command == RECARGAR){
            player->reload();
        } else if (command == AGACHARSE){
            player->agacharse();
        } else if (command == LEVANTARSE){
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
            //TODO: Cambiar para elegir un mapa random.

            mapa = std::make_unique<Mapa>(2);
            
            EventoMapa eventoMapa(mapa->getCollidables());
            monitor.enviar_evento(eventoMapa);
            Jugador* winner = get_winner();
            EventoWinRound eventoWinRound(winner->get_id());
            monitor.enviar_evento(eventoWinRound);
            reset_jugadores();
            ticks_round_win_screen = 60;
            should_reset_round = false;

        }
        return;
    }
    
    Jugador* winner = get_winner();
    if (winner) {
        std::cout << "found winner" << std::endl;
        should_reset_round = true;
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
void Gameloop::sleep() { std::this_thread::sleep_for(std::chrono::milliseconds(50)); }

void Gameloop::cerrar_conexiones(){
    for (auto it = jugadores.begin(); it != jugadores.end();) {        
        eliminar_jugador(it);
        ++it;
    }
}
