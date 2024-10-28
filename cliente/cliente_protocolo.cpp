#include "cliente_protocolo.h"

ClienteProtocolo::ClienteProtocolo(const char* hostname, const char* servname) : socket(hostname, servname) {}

bool ClienteProtocolo::recibir_evento(Evento &evento) {
    bool was_closed = false;
    return was_closed;

}

void ClienteProtocolo::cerrar_conexion() {
    socket.shutdown(2);
    socket.close();
}

ClienteProtocolo::~ClienteProtocolo() {}
