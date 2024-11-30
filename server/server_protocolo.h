#ifndef SERVER_PROTOCOLO_H
#define SERVER_PROTOCOLO_H

#include "../common/common_socket.h"
#include "../common/common_accion.h"
#include "../common/common_serializador.h"
#include "../common/common_evento.h"
#include "Collidable.h"
#include "Vector.h"
#include <mutex>

class ProtocoloServidor{
    private:
        Socket conexion;
        Serializador serializador;
        std::mutex mtx;

    public:
        explicit ProtocoloServidor(Socket&& conexion);
        Accion recibir_accion();
        
        bool enviar_id(int id);
        void enviar_estado(const Evento& evento); 
        Socket get_socket();  
        void cerrar_conexion();
};

#endif
