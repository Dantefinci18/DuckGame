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

    uint8_t data[8];
    conexion.recvall(data, sizeof(data), &was_closed);

    if (was_closed) {
        return NONE_ACCION;
    }

    return serializador.deserializar_accion(data);
}


std::unique_ptr<ComandoPartida> ProtocoloServidor::recibir_comando_partida() {
    bool was_closed = false;

    uint8_t tipo[8];
    int bytes_recibidos = conexion.recvall(tipo, sizeof(tipo), &was_closed);
    
    std::cout << "tipo partida:" << std::endl;
    serializador.imprimir_uint8_t_array(tipo,sizeof(tipo));

    if (was_closed || bytes_recibidos < sizeof(tipo)) {
        return std::make_unique<ComandoNonePartida>(ComandoNonePartida());
    }

    ComandoPartida::TipoComandoPartida tipo_partida = serializador.deserializar_tipo_comando_partida(tipo);

    if(tipo_partida == ComandoPartida::TipoComandoPartida::NUEVA_PARTIDA){
        uint8_t tamanio_nombre_bits[32];
        bytes_recibidos = conexion.recvall(tamanio_nombre_bits,sizeof(tamanio_nombre_bits),&was_closed);

        std::cout << "tamanio nombre partida:" << std::endl;
        serializador.imprimir_uint8_t_array(tamanio_nombre_bits,sizeof(tamanio_nombre_bits));

        if(was_closed)
            return std::make_unique<ComandoNonePartida>(ComandoNonePartida());
        int tamanio_nombre = serializador.deserializar_id(tamanio_nombre_bits);

        uint8_t nombre_bits[tamanio_nombre];
        bytes_recibidos = conexion.recvall(nombre_bits,sizeof(nombre_bits),&was_closed);

        if(was_closed)
            return std::make_unique<ComandoNonePartida>(ComandoNonePartida());

        std::cout << "nombre partida:" << std::endl;
        serializador.imprimir_uint8_t_array(nombre_bits,tamanio_nombre);
        
        uint8_t cantidad_de_jugadores[32];
        bytes_recibidos = conexion.recvall(cantidad_de_jugadores,sizeof(cantidad_de_jugadores),&was_closed);

        std::cout << "cantidad de jugadores partida:" << std::endl;
        serializador.imprimir_uint8_t_array(cantidad_de_jugadores,sizeof(cantidad_de_jugadores));

        if(bytes_recibidos < sizeof(tamanio_nombre) || was_closed)
            return std::make_unique<ComandoNonePartida>(ComandoNonePartida());
        
        
        std::string nombre(reinterpret_cast<char*>(nombre_bits),tamanio_nombre);
        std::cout << nombre << std::endl;
        return std::make_unique<ComandoNuevaPartida>(ComandoNuevaPartida(nombre,*cantidad_de_jugadores));
    }

    return std::make_unique<ComandoNonePartida>(ComandoNonePartida());
}


bool ProtocoloServidor::enviar_id(int id) {
    bool was_closed = false;
    std::vector<uint8_t> buffer= serializador.serializar_id(id);

    conexion.sendall(buffer.data(), buffer.size(), &was_closed);

    return !was_closed; 
}
void ProtocoloServidor::enviar_estado(const Evento& evento) {
    bool was_closed = false;
    
    std::vector<uint8_t> bits = serializador.serializar_evento(evento);
    
    evento.print();
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

Socket ProtocoloServidor::get_socket(){
    return std::move(conexion);
}

void ProtocoloServidor::cerrar_conexion() {
    conexion.shutdown(2);
    conexion.close();
}
