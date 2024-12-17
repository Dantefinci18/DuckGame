#include "server_lobby.h"

ServerLobby::ServerLobby(int id) : id(id) {}    

void ServerLobby::agregar_jugador(Socket& skt){
    id ++;
    Jugador *jugador = new Jugador(cola_comando_partidas,std::move(skt),id);
    jugador->run();
    jugadores_esperando[jugador->get_id()] = jugador;
}

void ServerLobby::run(){
    while(_keep_running){
        try{
            auto accion_partida = cola_comando_partidas.pop();
            eliminar_terminadas();
            int id_jugador = accion_partida.get_player_id();
            Jugador *jugador = jugadores_esperando[accion_partida.get_player_id()];
            ComandoAccion partida = accion_partida.get_command();

            if(partida == NONE_ACCION){
                jugador->stop();
                jugadores_esperando.erase(id_jugador);

            }else if(partida == NUEVA_PARTIDA){
                jugador->enviar_evento(EventoEspera());
                Gameloop *gameloop = new Gameloop(accion_partida.get_player_id(),2,jugador->get_cola_eventos());
                partidas.push_back(gameloop);
            
            }else if(partida == CARGAR_PARTIDA){
                Gameloop *gameloop = obtener_partida_en_espera();
                if(gameloop != nullptr){
                    gameloop->agregar_jugador(id_jugador,jugador->get_cola_eventos());
                    
                    if(gameloop->esta_llena()){
                        comenzar_partida(gameloop);
                    }else{
                        jugador->enviar_evento(EventoEspera());
                    }
                }

            }

       } catch (std::exception& e) {
            if (_keep_running)
                std::cerr << "Lobby error: " << e.what() << "\n";
        }
    }
}

void ServerLobby::comenzar_partida(Gameloop *partida){
    for(int id_jugador : partida->get_ids()){
        auto jugador = jugadores_esperando[id_jugador];
        jugador->reset(partida->get_cola_acciones());
    }

    partida->start();
}

Gameloop *ServerLobby::obtener_partida_en_espera(){
    for(auto& partida : partidas){
        if(!partida->esta_llena()){
            return partida;
        }
    }

    return nullptr;
}

void ServerLobby::eliminar_terminadas(){
    for (auto it = partidas.begin(); it != partidas.end();) {
        Gameloop* partida = *it;
        if (partida->esta_vacia()) {
            it = partidas.erase(it);
            eliminar_jugadores_de_una_partida(partida);
            partidas.remove(partida);
            delete partida;
        
        } else {
            ++it;
        }
    }

}

void ServerLobby::eliminar_jugadores_de_una_partida(Gameloop *partida){

    for(int id_jugador : partida->get_ids()){
        Jugador *jugador = jugadores_esperando[id_jugador];
        partida->eliminar_jugador(id_jugador,jugador->get_cola_eventos());
        delete jugador;
    }
}

void ServerLobby::eliminar_partidas(){
     for (auto partida: partidas) {
        partida->stop();
        eliminar_jugadores_de_una_partida(partida);
        partida->join();
        delete partida;
    }

    partidas.clear();
}

void ServerLobby::finalizar(){
    this->stop();
    cola_comando_partidas.close();
    eliminar_partidas();
    cerrar_conexiones();
    this->join();
}

void ServerLobby::cerrar_conexiones(){
    for(auto pair : jugadores_esperando){
        pair.second->stop();
    }

    jugadores_esperando.clear();
}