#include "server_protocolo.h"
#include <utility>
#include <stdexcept>
#include <bitset> 
#include <cstring> 
#include <iostream> 
#include <vector> 
#include <cstdint> 

ProtocoloServidor::ProtocoloServidor(Socket&& conexion): conexion(std::move(conexion)) {}


ComandoAccion ProtocoloServidor::recibir_accion() {
    bool was_closed = false;

    uint8_t data[8];
    conexion.recvall(data, sizeof(data), &was_closed);

    if (was_closed) {
        return NONE;
    }

    return serializador.deserializar_accion(data);
}

bool ProtocoloServidor::enviar_id(int id) {
    bool was_closed = false;
    std::vector<uint8_t> buffer= serializador.serializar_id(id);

    conexion.sendall(buffer.data(), buffer.size(), &was_closed);

    return !was_closed; 
}

void ProtocoloServidor::enviar_estado(Evento evento) {
    bool was_closed = false;

    std::vector<uint8_t> bits = serializador.serializar_evento(evento);
    
    conexion.sendall(bits.data(), bits.size(), &was_closed);
    if (was_closed) {
        throw std::runtime_error("Error al enviar estado");
    }
}

/*
- EVENTO_SPAWN_JUGADOR(id_jugador, x, y,...)
- EVENTO_MOVIMIENTO_JUGADOR (id_jugador, x, y,...)
- EVENTO_SPAWN_OBJETO(id_objeto, x, y)
- EVENTO_DISPARAR(id_jugador)
- EVENTO_PICKUP(id_objeto, id_jugador)
***** Hasta acá sirve el enviar_evento (devberia llamarse asi más que enviar_estado)

- EVENTO_ESTADO_ACTUAL(jugadores, objetos, mapa) <- esto se enviaria al principio cuando se une un jugador.
*/



void ProtocoloServidor::cerrar_conexion() {
    conexion.shutdown(2);
    conexion.close();
}
