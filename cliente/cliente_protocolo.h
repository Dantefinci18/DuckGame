#ifndef CLIENTE_PROTOCOLO_H
#define CLIENTE_PROTOCOLO_H

#include "../common/common_socket.h"
#include "../common/common_evento.h"
#include "../common/common_accion.h"
#include "../common/common_serializador.h"
class ClienteProtocolo{
    public:
        explicit ClienteProtocolo(Socket&& socket);
        void cerrar_conexion();
        bool enviar_accion(ComandoAccion &accion);
        int recibir_id();
        std::unique_ptr<Evento> recibir_evento();

    private:
        Socket socket;
        Serializador serializador;
};

#endif