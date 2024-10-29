#include "server_protocolo.h"
#include <utility>
#include <stdexcept>

ProtocoloServidor::ProtocoloServidor(Socket&& conexion): conexion(std::move(conexion)) {}

ComandoAccion ProtocoloServidor::recibir_accion() {
    bool was_closed = false;

    uint8_t data[8];
    conexion.recvall(data, sizeof(data), &was_closed);

    if (was_closed) {
        throw std::runtime_error("Error al recibir accion");
    }

    uint8_t accion_valor = 0;
    for (int i = 0; i < 8; ++i) {
        accion_valor = (data[7 - i] << i); 
    }

    ComandoAccion accion = static_cast<ComandoAccion>(accion_valor);
    return accion;
}


void ProtocoloServidor::cerrar_conexion() {
    conexion.shutdown(2);
    conexion.close();
}
