#ifndef CLIENTE_PROTOCOLO_H
#define CLIENTE_PROTOCOLO_H

#include "../common/common_socket.h"
#include "../common/common_evento.h"
#include "../common/common_accion.h"
#include "../common/common_serializador.h"
#include "../server/Collidable.h"
#include <vector>
#include <memory>

class ClienteProtocolo{
    public:
        explicit ClienteProtocolo(Socket&& socket);
        void cerrar_conexion();
        bool enviar_accion(ComandoAccion &accion);
        int recibir_id();
        std::unique_ptr<Evento> recibir_evento();
        std::vector<Collidable*> recibir_mapa();

    private:
        Socket socket;
        Serializador serializador;
};

#endif