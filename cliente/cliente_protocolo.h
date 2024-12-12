#ifndef CLIENTE_PROTOCOLO_H
#define CLIENTE_PROTOCOLO_H

#include "../common/common_socket.h"
#include "../common/common_evento.h"
#include "../common/common_accion.h"
#include "../common/common_serializador.h"
#include "../server/Collidable.h"
#include "../server/server_leaderboard.h"
#include <vector>
#include <memory>
#include <unordered_map>

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
        bool enviar_accion(ComandoAccion &comando_accion);

        bool crear_partida(const std::string& nombre_partida,
                const std::string& mapa_seleccionado, const unsigned int cantidad_de_jugadores);
        
        bool cargar_partida(int id, const std::string& nombre_partida);

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

        std::list<Partida> recibir_partidas();

    private:
        Socket socket;
        Serializador serializador;
};

#endif