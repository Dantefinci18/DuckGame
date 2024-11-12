#include "lobby.h"
#include <utility>
#include "cliente_protocolo.h"
Lobby::Lobby(const char* hostname, const char* servname) : socket(hostname, servname) {}

void Lobby::crear_partida(const std::string& mapa_seleccionado) {
    std::string comando = "crear_partida " + mapa_seleccionado;
    return;
    
}


Lobby::~Lobby() {}

Socket Lobby::get_socket() {
    return std::move(socket);
}