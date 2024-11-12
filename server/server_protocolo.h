#ifndef SERVER_PROTOCOLO_H
#define SERVER_PROTOCOLO_H

#include "common/common_socket.h"
#include "common/common_accion.h"
#include "common/common_serializador.h"
#include "Vector.h"

class ProtocoloServidor{
    private:
        Socket conexion;
        Serializador serializador;

    public:
        explicit ProtocoloServidor(Socket&& conexion);
        ComandoAccion recibir_accion();
        
        bool enviar_id(int id);
        void enviar_estado(const Evento& evento);

        void cerrar_conexion();
};

#endif
