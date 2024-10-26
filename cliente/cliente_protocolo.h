#ifndef CLIENTE_PROTOCOLO_H
#define CLIENTE_PROTOCOLO_H

#include "../common/common_socket.h"

class ClienteProtocolo{
    public:
        explicit ClienteProtocolo(const char* hostname, const char* servname);
        void cerrar_conexion();
        ~ClienteProtocolo();

    private:
        Socket socket;

};

#endif