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


std::shared_ptr<Accion> ProtocoloServidor::recibir_accion() {
    bool was_closed = false;

    uint8_t data_tipo[ACCION_RECIBIDA];
    conexion.recvall(data_tipo, sizeof(data_tipo), &was_closed);

    if (was_closed) {
        return std::make_unique<Accion>(NONE_ACCION);
    }

    std::cout << "tipo accion:\n";
    serializador.imprimir_uint8_t_array(data_tipo,sizeof(data_tipo));
    ComandoAccion tipo_accion = serializador.deserializar_tipo_accion(data_tipo);

    if(tipo_accion == NUEVA_PARTIDA){
        uint8_t data_cantidad_de_jugadores[32];
        conexion.recvall(data_cantidad_de_jugadores,sizeof(data_cantidad_de_jugadores),&was_closed);

        if (was_closed) {
            return std::make_shared<Accion>(NONE_ACCION);
        }

        std::cout << "cantidad de jugadores:\n";
        serializador.imprimir_uint8_t_array(data_cantidad_de_jugadores,sizeof(data_cantidad_de_jugadores));
        uint8_t data_mapa[32];
        conexion.recvall(data_mapa,sizeof(data_mapa),&was_closed);

        if (was_closed) {
            return std::make_shared<Accion>(NONE_ACCION);
        }
        std::cout << "mapa:\n";
        serializador.imprimir_uint8_t_array(data_mapa,sizeof(data_mapa));

        uint8_t data_tamanio_nombre[32];
        conexion.recvall(data_tamanio_nombre,sizeof(data_tamanio_nombre),&was_closed);

        if (was_closed) {
            return std::make_unique<Accion>(NONE_ACCION);
        }
        std::cout << "tamanio nombre partida:\n";
        serializador.imprimir_uint8_t_array(data_tamanio_nombre,sizeof(data_tamanio_nombre));

        int tamanio_nombre = serializador.deserializar_numero_entero(data_tamanio_nombre);

        uint8_t data_nombre_partida[tamanio_nombre];
        conexion.recvall(data_nombre_partida,sizeof(data_nombre_partida),&was_closed);

        std::cout << "nombre partida:\n";
        serializador.imprimir_uint8_t_array(data_nombre_partida,sizeof(data_nombre_partida));

        auto nuevaPartida = serializador.deserializar_nueva_partida(data_nombre_partida,tamanio_nombre,data_cantidad_de_jugadores,data_mapa);
        std::cout << "nombre partida en protocolo: \n" << nuevaPartida->nombre_partida << std::endl;
        return nuevaPartida;

    }else if(tipo_accion == CARGAR_PARTIDA){
        uint8_t data_id_partida[32];
        conexion.recvall(data_id_partida,sizeof(data_id_partida),&was_closed);

        if (was_closed) {
            return std::make_shared<Accion>(NONE_ACCION);
        }

        std::cout << "id_partida:\n";
        serializador.imprimir_uint8_t_array(data_id_partida,sizeof(data_id_partida)); 
        
        int id_partida = serializador.deserializar_numero_entero(data_id_partida);
        return   std::make_shared<AccionCargarPartida>(id_partida);
    }

    return std::make_shared<Accion>(tipo_accion);

}



bool ProtocoloServidor::enviar_id(int id) {
    bool was_closed = false;
    std::vector<uint8_t> buffer = serializador.serializar_id(id);

    conexion.sendall(buffer.data(), buffer.size(), &was_closed);

    return !was_closed; 
}
void ProtocoloServidor::enviar_estado(const Evento& evento) {
    std::lock_guard<std::mutex> lock(mtx);
    bool was_closed = false;
    
    std::vector<uint8_t> bits = serializador.serializar_evento(evento);
    
    evento.print();
    conexion.sendall(bits.data(), bits.size(), &was_closed);
    if (was_closed) {
        throw std::runtime_error("Error al enviar estado");
    }

    std::cout << "envio evento\n";
    serializador.imprimir_uint8_t_array(bits.data(),bits.size());

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

bool ProtocoloServidor::enviar_partidas(std::list<Partida> &partidas){
    bool was_closed = false;
    std::vector<uint8_t> bits_tamanio_partidas(32);
    serializador.serializar_numero_entero(partidas.size(),bits_tamanio_partidas,0);
    std::cout<< "tamanio partidas\n";
    serializador.imprimir_uint8_t_array(bits_tamanio_partidas.data(),bits_tamanio_partidas.size());
    conexion.sendall(bits_tamanio_partidas.data(),bits_tamanio_partidas.size(),&was_closed);

    if(was_closed){
        return false;
    }

    for(auto& partida : partidas){
        auto partida_bits = serializador.serializar_partida(partida);
        conexion.sendall(partida_bits.data(),partida_bits.size(),&was_closed);

        if(was_closed){
            return false;
        }

        std::vector<uint8_t> nombre_bits(0);
        serializador.serializar_string(partida.nombre,nombre_bits,0);
        conexion.sendall(nombre_bits.data(),nombre_bits.size(),&was_closed);

        if(was_closed){
            return false;
        }

    }

    return true;
}

Socket ProtocoloServidor::get_socket(){
    return std::move(conexion);
}

void ProtocoloServidor::cerrar_conexion() {
    conexion.shutdown(2);
    conexion.close();
}
