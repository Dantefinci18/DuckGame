#ifndef JUGADOR_ESPERANDO_H
#define JUGADOR_ESPERANDO_H

#include "../common/common_socket.h"
#include "server_protocolo.h"
#include "../common/common_partida.h"
#include "../common/common_thread.h"
#include "../common/common_queue.h"
#include "../common/common_partida.h"
#include <tuple>

class JugadorEsperando : public Thread{
    private:
        ProtocoloServidor protocolo;
        Queue<std::tuple<int,std::unique_ptr<ComandoPartida>>>& cola_comandos_partidas;
        int id;

        int generar_id();
        
    public:
        explicit JugadorEsperando(Socket&& skt, 
            Queue<std::tuple<int,std::unique_ptr<ComandoPartida>>>& cola_comandos_partidas);

        void run() override;
        int get_id();
        Socket get_socket();
};

#endif