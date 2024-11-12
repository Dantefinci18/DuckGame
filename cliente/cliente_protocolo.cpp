#include "cliente_protocolo.h"
#include <ostream>
#include <bitset>
#include <iostream>
#include <cstring>
#include <memory> 


ClienteProtocolo::ClienteProtocolo(Socket&& socket) : socket(std::move(socket)) {}


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

std::unique_ptr<Evento> ClienteProtocolo::recibir_evento() {
    bool was_closed = false;

    uint8_t tipo_evento[8];
    socket.recvall(tipo_evento, sizeof(tipo_evento), &was_closed);
    if (was_closed) {
        return nullptr;
    }

    uint8_t x[32];
    socket.recvall(x, sizeof(x), &was_closed);
    if (was_closed) {
        return nullptr;
    }

    uint8_t y[32];
    socket.recvall(y, sizeof(y), &was_closed);
    if (was_closed) {
        return nullptr;
    }

    uint8_t id[32];
    socket.recvall(id, sizeof(id), &was_closed);
    if (was_closed) {
        return nullptr;
    }

    return serializador.deserializar_evento(tipo_evento,id, x, y);
}

void ClienteProtocolo::cerrar_conexion() {
    socket.shutdown(2);
    socket.close();
}
