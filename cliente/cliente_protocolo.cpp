#include "cliente_protocolo.h"
#include <ostream>
#include <bitset>
#include <iostream>
#include <cstring>


ClienteProtocolo::ClienteProtocolo(const char* hostname, const char* servname) : socket(hostname, servname) {}
#include <bitset>
#include <string>
#include <iostream>

bool ClienteProtocolo::enviar_accion(ComandoAccion &accion) {
    bool was_closed = false;

    std::vector<uint8_t> buffer= serializador.serializar_accion(accion);

    socket.sendall(buffer.data(), buffer.size(), &was_closed);

    return !was_closed;  
}

int ClienteProtocolo::recibir_id() {
    bool was_closed = false;
    uint8_t data[32];
    socket.recvall(data, sizeof(data), &was_closed);

    if (was_closed) {
        return -1;
    }
    return serializador.deserializar_id(data);
}

bool ClienteProtocolo::recibir_evento(Evento &evento) {
    bool was_closed = false;

    uint8_t x[32];
    socket.recvall(x, sizeof(x), &was_closed);
    if (was_closed) {
        return false;
    }

    uint8_t y[32];
    socket.recvall(y, sizeof(y), &was_closed);
    if (was_closed) {
        return false;
    }

    uint8_t id[32];
    socket.recvall(id, sizeof(id), &was_closed);
    if (was_closed) {
        return false;
    }

    evento = serializador.deserializar_evento(id, x, y);

    return !was_closed;
}

void ClienteProtocolo::cerrar_conexion() {
    socket.shutdown(2);
    socket.close();
}
