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
        throw std::runtime_error("Error al recibir accion");
    }

    return serializador.deserializar_accion(data);
}


void ProtocoloServidor::enviar_estado(Vector posicion) {
    bool was_closed = false;

    Evento evento;
    evento.x = posicion.x;
    evento.y = posicion.y;

    std::vector<uint8_t> bits = serializador.serializar_evento(evento);
    
    conexion.sendall(bits.data(), bits.size(), &was_closed);
    if (was_closed) {
        throw std::runtime_error("Error al enviar estado");
    }
}













void ProtocoloServidor::cerrar_conexion() {
    conexion.shutdown(2);
    conexion.close();
}
