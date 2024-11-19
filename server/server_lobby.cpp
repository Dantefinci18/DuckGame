#include "server_lobby.h"

void ServerLobby::agregar_jugador(Socket& skt){
    JugadorEsperando *jugador = new JugadorEsperando(std::move(skt),cola_comando_partidas);
    jugadores_esperando[jugador->get_id()] = jugador;
    jugador->start();
}

void ServerLobby::run(){
    while(_keep_running){
        try{
            auto tupla_partida = cola_comando_partidas.pop();
            eliminar_terminadas();

            int id_jugador = std::get<0>(tupla_partida);
            JugadorEsperando *jugador = jugadores_esperando[id_jugador];
            Socket skt = jugador->get_socket();
            ComandoPartida partida = std::get<1>(tupla_partida);

            if(partida == NONE_PARTIDA){
                skt.shutdown(2);
                skt.close();
                jugadores_esperando.erase(id_jugador);
                jugador->stop();
                jugador->join();
                delete jugador;

            }else if(partida == NUEVA_PARTIDA){
                Gameloop *gameloop = new Gameloop(skt,2);
                partidas.push_back(gameloop);
                jugadores_esperando.erase(id_jugador);
                jugador->stop();
                jugador->join();
                delete jugador;
            
            }else if(partida == CARGAR_PARTIDA){
                Gameloop *gameloop = obtener_partida_en_espera();
                gameloop->agregar_jugador(skt);
                jugadores_esperando.erase(id_jugador);
                jugador->stop();
                jugador->join();
                delete jugador;

            }

       } catch (std::exception& e) {
            if (_keep_running)
                std::cerr << "Lobby error: " << e.what() << "\n";
        }
    }
}

Gameloop *ServerLobby::obtener_partida_en_espera(){
    for(auto& partida : partidas){
        if(partida->get_estado() == EN_ESPERA){
            return partida;
        }
    }
}

void ServerLobby::eliminar_terminadas(){
    for (auto it = partidas.begin(); it != partidas.end();) {
        Gameloop* partida = *it;
        if (partida->get_estado() == TERMINADA) {
            it = partidas.erase(it);
            partidas.remove(partida);
            partida->cerrar_conexiones();
            delete partida;
        
        } else {
            ++it;
        }
    }

}

void ServerLobby::eliminar_partidas(){
     for (auto partida: partidas) {
        partida->stop();
        partida->cerrar_conexiones();
        delete partida;
    }

    partidas.clear();
}

void ServerLobby::finalizar(){
    this->stop();
    cola_comando_partidas.close();
    eliminar_partidas();
    this->join();
}