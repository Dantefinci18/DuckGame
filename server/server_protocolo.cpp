#include "server_protocolo.h"
#include <utility>
#include <stdexcept>

ProtocoloServidor::ProtocoloServidor(Socket&& conexion): conexion(std::move(conexion)) {}

ComandoAccion ProtocoloServidor::recibir_accion() {
    bool was_closed = false;
    ComandoAccion accion;
    conexion.recvall(&accion, sizeof(accion), &was_closed);
    if (was_closed) {
        throw std::runtime_error("Error al recibir accion");
    }
    return accion;
    
}

void ProtocoloServidor::cerrar_conexion() {
    conexion.shutdown(2);
    conexion.close();
}
