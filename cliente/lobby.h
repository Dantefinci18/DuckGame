#ifndef LOBBY_H
#define LOBBY_H

#include "../common/common_socket.h"
#include "../common/common_serializador.h"
#include "cliente_protocolo.h"
#include <vector>
#include "../server/Collidable.h"
#include "../server/server_leaderboard.h"
#include <memory>
#include "../common/common_evento.h"


class Lobby {
public:
    /*
     * Constructor de la clase Lobby, recibe un hostname y un servname
     */
    Lobby(const char* hostname, const char* servname);
    /*
     * Funcion que crea una partida
     * Recibe un string con el mapa seleccionado
     */
    void crear_partida(const std::string& mapa_seleccionado);

    void cargar_partida();

    /*
     * Funcion que se une a una partida
     * Recibe un string con el nombre de la partida
     */
    
    int recibir_id();

    /*
     * Funcion que recibe un evento
     * y lo retorna
     * 
     */
    std::unique_ptr<Evento> recibir_evento();

    ~Lobby();
    Socket get_socket();
private:
    Socket socket;
    Serializador serializador;

  
};

#endif // LOBBY_H