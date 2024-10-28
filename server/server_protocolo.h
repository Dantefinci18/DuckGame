#ifndef SERVER_PROTOCOLO_H
#define SERVER_PROTOCOLO_H

#include "common/common_socket.h"

class ProtocoloServidor{
    private:
        Socket conexion;

    public:
        explicit ProtocoloServidor(Socket&& conexion);

        void cerrar_conexion();
};

#endif
