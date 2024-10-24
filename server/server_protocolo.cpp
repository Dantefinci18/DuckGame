#include "server_protocolo.h"
#include <utility>

ProtocoloServidor::ProtocoloServidor(Socket&& conexion): conexion(std::move(conexion)) {}

void ProtocoloServidor::cerrar_conexion() {
    conexion.shutdown(2);
    conexion.close();
}
