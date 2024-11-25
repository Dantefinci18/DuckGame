#ifndef SERVER_PROTOCOLO_H
#define SERVER_PROTOCOLO_H

#include "common/common_socket.h"
#include "common/common_accion.h"
#include "common/common_serializador.h"
#include "common/common_evento.h"
#include "Collidable.h"
#include "Vector.h"

class ProtocoloServidor{
    private:
        Socket conexion;
        Serializador serializador;

    public:
        explicit ProtocoloServidor(Socket&& conexion);
        ComandoAccion recibir_accion();
        std::unique_ptr<ComandoPartida> recibir_comando_partida();
        
        bool enviar_id(int id);
        void enviar_estado(const Evento& evento); 
        Socket get_socket();  
        void cerrar_conexion();
};

#endif
