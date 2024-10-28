#ifndef SERVER_PROTOCOLO_H
#define SERVER_PROTOCOLO_H

#include "common/common_socket.h"
#include "common/common_accion.h"

class ProtocoloServidor{
    private:
        Socket conexion;

    public:
        explicit ProtocoloServidor(Socket&& conexion);
        ComandoAccion recibir_accion();

        void cerrar_conexion();
};

#endif
