#ifndef LOBBY_H
#define LOBBY_H

#include "../common/common_socket.h"
#include "../common/common_serializador.h"
#include "cliente_protocolo.h"
#include <vector>
#include "../server/Collidable.h"
#include <memory>
#include "../common/common_evento.h"


class Lobby {
public:
    Lobby(const char* hostname, const char* servname);
    void crear_partida(const std::string& mapa_seleccionado);
    int recibir_id();
    std::unique_ptr<Evento> recibir_evento();

    ~Lobby();
    Socket get_socket();
private:
    Socket socket;
    Serializador serializador;

  
};

#endif // LOBBY_H