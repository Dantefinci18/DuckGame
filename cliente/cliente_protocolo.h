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

        /*
         * Constructor de la clase ClienteProtocolo, recibe un socket
         */
        explicit ClienteProtocolo(Socket&& socket);

        /*
         * Funcion que cierra la conexion
         */
        void cerrar_conexion();

        /*
         * Funcion que envia una accion
         * Recibe un ComandoAccion
         */
        bool enviar_accion(ComandoAccion &accion);

        /*
         * Funcion que recibe un id
         * y lo retorna
         */
        int recibir_id();

        /*
         * Funcion que recibe un evento
         * y lo retorna
         */
        std::unique_ptr<Evento> recibir_evento();

        /*
         * Funcion que recibe el mapa
         * y lo retorna
         */
        std::vector<Collidable*> recibir_mapa();

    private:
        Socket socket;
        Serializador serializador;
};

#endif