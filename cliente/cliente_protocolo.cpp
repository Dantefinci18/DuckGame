#include "cliente_protocolo.h"

ClienteProtocolo::ClienteProtocolo(const char* hostname, const char* servname) : socket(hostname, servname) {}

void ClienteProtocolo::cerrar_conexion() {
    socket.shutdown(2);
    socket.close();
}

ClienteProtocolo::~ClienteProtocolo() {}
