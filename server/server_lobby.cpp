#include "server_lobby.h"

ServerLobby::ServerLobby(int id) : id(id) {}    

void ServerLobby::agregar_jugador(Socket& skt){
    id++;
    Jugador *jugador = new Jugador(cola_comando_partidas, std::move(skt), id);
    jugador->run();
    jugadores_esperando[jugador->get_id()] = jugador;
}

void ServerLobby::run(){
    while (_keep_running) {
        try {
            auto accion_partida = cola_comando_partidas.pop();
            eliminar_terminadas();
            int id_jugador = accion_partida.get_player_id();
            Jugador *jugador = jugadores_esperando[accion_partida.get_player_id()];
            ComandoAccion partida = accion_partida.get_command();

            if (partida == NONE_ACCION) {
                jugador->stop();
                jugadores_esperando.erase(id_jugador);

            } else if (partida == NUEVA_PARTIDA) {
                int cantidad_jugadores = accion_partida.get_cantidad_jugadores();
                jugador->enviar_evento(EventoEspera());
                Gameloop *gameloop = new Gameloop(accion_partida.get_player_id(), cantidad_jugadores, jugador->get_cola_eventos());
                partidas.insert({contador_partidas++, gameloop});
            
            } else if (partida == CARGAR_PARTIDA) {
                std::cout << "Cargar partida" << std::endl;
                Gameloop *gameloop = obtener_partida_en_espera();
                if (gameloop != nullptr) {
                    gameloop->agregar_jugador(id_jugador, jugador->get_cola_eventos());
                    
                    if (gameloop->esta_llena()) {
                        comenzar_partida(gameloop);
                    } else {
                        jugador->enviar_evento(EventoEspera());
                    }
                }

            } else { 
                std::cerr << "Comando desconocido\n";
            }

        } catch (std::exception& e) {
            if (_keep_running)
                std::cerr << "Lobby error: " << e.what() << "\n";
        }
    }
}

void ServerLobby::comenzar_partida(Gameloop *partida) {
    for (int id_jugador : partida->get_ids()) {
        auto jugador = jugadores_esperando[id_jugador];
        jugador->reset(partida->get_cola_acciones());
    }

    partida->start();
}

Gameloop *ServerLobby::obtener_partida_en_espera() {
    for (auto& partida : partidas) {
        if (!partida.second->esta_llena()) {
            return partida.second;
        }
    }

    return nullptr;
}

void ServerLobby::eliminar_terminadas() {
    std::lock_guard<std::mutex> lock(mtx);
    for (auto it = partidas.begin(); it != partidas.end();) {
        Gameloop* partida = it->second;
        if (partida->esta_vacia()) {
            eliminar_jugadores_de_una_partida(partida);
            delete partida;
            it = partidas.erase(it);  
        } else {
            ++it;
        }
    }
}

void ServerLobby::eliminar_jugadores_de_una_partida(Gameloop *partida) {
    std::cout << "elimino partida" << std::endl;

    for (int id_jugador : partida->get_ids()) {
        std::cout << "elimino jugador: " << id_jugador << std::endl;
        Jugador *jugador = jugadores_esperando[id_jugador];
        partida->eliminar_jugador(id_jugador, jugador->get_cola_eventos());
        delete jugador;
    }
}

void ServerLobby::eliminar_partidas() {
    std::lock_guard<std::mutex> lock(mtx);
    for (auto& partida : partidas) {
        partida.second->stop();
        eliminar_jugadores_de_una_partida(partida.second);
        partida.second->join();
        delete partida.second;
    }

    partidas.clear();
}

void ServerLobby::finalizar() {
    this->stop();
    cola_comando_partidas.close();
    eliminar_partidas();
    cerrar_conexiones();
    this->join();
}

void ServerLobby::cerrar_conexiones() {
    for (auto pair : jugadores_esperando) {
        pair.second->stop();
    }

    jugadores_esperando.clear();
}
