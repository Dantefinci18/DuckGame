#ifndef CLIENTE_PROTOCOLO_H
#define CLIENTE_PROTOCOLO_H

#include "../common/common_socket.h"
#include "../common/common_evento.h"
#include "../common/common_accion.h"
class ClienteProtocolo{
    public:
        explicit ClienteProtocolo(const char* hostname, const char* servname);
        void cerrar_conexion();
        bool enviar_accion(ComandoAccion &accion);
        bool recibir_evento(Evento &evento);
        ~ClienteProtocolo();

    private:
        Socket socket;

};

#endif