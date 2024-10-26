#ifndef CLIENTE_PROTOCOLO_H
#define CLIENTE_PROTOCOLO_H

#include "../common/common_socket.h"
#include "../common/common_evento.h"
class ClienteProtocolo{
    public:
        explicit ClienteProtocolo(const char* hostname, const char* servname);
        void cerrar_conexion();
        bool recibir_evento(Evento &evento);
        ~ClienteProtocolo();

    private:
        Socket socket;

};

#endif