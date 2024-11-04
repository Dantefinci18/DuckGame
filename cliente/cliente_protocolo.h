#ifndef CLIENTE_PROTOCOLO_H
#define CLIENTE_PROTOCOLO_H

#include "../common/common_socket.h"
#include "../common/common_evento.h"
#include "../common/common_accion.h"
#include "../common/common_serializador.h"
class ClienteProtocolo{
    public:
        explicit ClienteProtocolo(const char* hostname, const char* servname);
        void cerrar_conexion();
        bool enviar_accion(ComandoAccion &accion);
        int recibir_id();
        bool recibir_evento(Evento &evento);

    private:
        Socket socket;
        Serializador serializador;
};

#endif