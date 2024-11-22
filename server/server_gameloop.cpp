#include "server_gameloop.h"

#include "../common/common_evento.h"
#include "../common/common_color.h"


Gameloop::Gameloop(): mapa(1),color(0) {}

void Gameloop::agregar_jugador(Socket& skt) {

    ColorDuck color_asignado = static_cast<ColorDuck>(color % static_cast<int>(ColorDuck::MAX_COLOR));


    Jugador* jugador = new Jugador(comandos_acciones, monitor, std::move(skt), color_asignado);


    jugador->run();
    jugadores[jugador->get_id()] = jugador;

    color++;
    }


    
void Gameloop::eliminar_jugador(std::unordered_map<int, Jugador*>::iterator& it){
   it->second->stop();
   delete it->second;
}

void Gameloop::eliminar_desconectados(){
    for (auto it = jugadores.begin(); it != jugadores.end();) {        
        if (!it->second->esta_conectado()) {
            it->second->stop();
            delete it->second;
            it = jugadores.erase(it);
        
        } else {
            ++it;
        }
    }
}

void Gameloop::run() {
    while (_keep_running) {
        cargar_acciones();
        sleep();
    }
}

void Gameloop::procesar_acciones(std::vector<Accion> acciones, std::vector<Collidable*> collidables){
    for (auto& accion : acciones) {
        
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
        
        } else if (command == NUEVA_PARTIDA_ACCION){
            EventoMapa eventoMapa(collidables);
            monitor.enviar_evento(eventoMapa);
            return;
        } else if (command == DISPARAR){
            std::vector<std::shared_ptr<Evento>> eventos;
            if(player->has_weapon()){
                DisparoManager::procesar_disparo(*player, collidables, jugadores, eventos);
            }
        } else if (command == DEJAR_DISPARAR){
            std::cout << "Dejo de disparar" << std::endl;
            player->dejar_disparar();
        } else if (command == RECARGAR){
            player->reload();
        } else if (command == APUNTAR_ARRIBA){
            player->apuntar_arriba();
        } else if (command == DEJAR_APUNTAR_ARRIBA){
            player->dejar_apuntar_arriba();
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
    
    procesar_acciones(acciones, mapa.getCollidables());
}

void Gameloop::sleep() { std::this_thread::sleep_for(std::chrono::milliseconds(50)); }

void Gameloop::cerrar_conexiones(){
    for (auto it = jugadores.begin(); it != jugadores.end();) {        
        eliminar_jugador(it);
        ++it;
    }
}
