#ifndef SERVER_LOBBY_H
#define SERVER_LOBBY_H

#include "server_gameloop.h"
#include "../common/common_socket.h"
#include "../common/common_thread.h"
#include "../common/common_queue.h"
#include "jugador_esperando.h"
#include <list>

class ServerLobby : public Thread {
    private:
        std::list<Gameloop*> partidas;
        Queue<std::tuple<int,ComandoPartida>> cola_comando_partidas;
        std::unordered_map<int, JugadorEsperando*> jugadores_esperando;
        std::mutex mtx;

        Gameloop *obtener_partida_en_espera();
        void cerrar_gameloops_terminados();
        void eliminar_terminadas();
        void eliminar_partidas();

    public:
        void agregar_jugador(Socket& skt);
        void finalizar();
        void run() override;
};

#endif