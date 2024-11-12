#include "lobby.h"
#include <utility>
#include <stdexcept>
#include "cliente_protocolo.h"
Lobby::Lobby(const char* hostname, const char* servname) : socket(hostname, servname) {}

void Lobby::crear_partida(const std::string& mapa_seleccionado) {
    bool was_closed = false;
    ComandoAccion comando = ComandoAccion::NUEVA_PARTIDA;
    std::vector<uint8_t> accion_serializada = serializador.serializar_accion(comando);
    socket.sendall(accion_serializada.data(), accion_serializada.size(), &was_closed);
    if (was_closed) {
        throw std::runtime_error("Error al enviar comando de nueva partida");
    }
    
}


Lobby::~Lobby() {}

Socket Lobby::get_socket() {
    return std::move(socket);
}