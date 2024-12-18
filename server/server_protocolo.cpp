#include "server_protocolo.h"
#include <utility>
#include <stdexcept>
#include <bitset> 
#include <cstring> 
#include <iostream> 
#include <vector> 
#include <cstdint> 
#include "../common/common_evento.h"

ProtocoloServidor::ProtocoloServidor(Socket&& conexion): conexion(std::move(conexion)) {}


ComandoAccion ProtocoloServidor::recibir_accion() {
    bool was_closed = false;

    std::vector<uint8_t> data(ACCION_RECIBIDA);
    conexion.recvall(data.data(), data.size(), &was_closed);

    if (was_closed) {
        return NONE_ACCION;
    }

    return serializador.deserializar_accion(data.data());
}



bool ProtocoloServidor::enviar_id(int id) {
    bool was_closed = false;
    std::vector<uint8_t> buffer = serializador.serializar_id(id);

    conexion.sendall(buffer.data(), buffer.size(), &was_closed);

    return !was_closed; 
}
void ProtocoloServidor::enviar_estado(const Evento& evento) {
    bool was_closed = false;
    
    std::vector<uint8_t> bits = serializador.serializar_evento(evento);
    
    //evento.print();
    conexion.sendall(bits.data(), bits.size(), &was_closed);
    if (was_closed) {
        throw std::runtime_error("Error al enviar estado");
    }

    /*
    switch (evento.get_tipo()){
        case Evento::EventoMovimiento: {
            std::vector<uint8_t> bits = serializador.serializar_evento(evento);
            conexion.sendall(bits.data(), bits.size(), &was_closed);
            if (was_closed) {
                throw std::runtime_error("Error al enviar estado");
            }
            break;
        }
        case Evento::EventoMapa: {
            std::vector<uint8_t> bits = serializador.serializar_mapa(evento);
            conexion.sendall(bits.data(), bits.size(), &was_closed);
            if (was_closed) {
                throw std::runtime_error("Error al enviar estado");
            }
            break;
        }
    }*/
}

int ProtocoloServidor::recibir_cantidad_jugadores() {
    bool was_closed = false;
    uint8_t data[4];
    conexion.recvall(data, sizeof(data), &was_closed);

    if (was_closed) {
        throw std::runtime_error("Error al recibir cantidad de jugadores");
    }

    return serializador.deserializar_cantidad_jugadores(data);
}


Socket ProtocoloServidor::get_socket(){
    return std::move(conexion);
}

void ProtocoloServidor::cerrar_conexion() {
    conexion.shutdown(2);
    conexion.close();
}
