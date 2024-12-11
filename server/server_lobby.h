#ifndef SERVER_LOBBY_H
#define SERVER_LOBBY_H

#include "server_gameloop.h"
#include "../common/common_socket.h"
#include "../common/common_thread.h"
#include "../common/common_queue.h"
#include "../common/common_accion.h"
#include "server_jugador.h"
#include "../common/common_partida.h"
#include <list>

class ServerLobby : public Thread {
    private:
        std::unordered_map<int,Gameloop*> partidas;
        Queue<std::shared_ptr<Accion>> cola_comando_partidas;
        int id;
        std::unordered_map<int, Jugador*> jugadores_esperando;
        std::mutex mtx;
        int cantidad_de_partidas = 0;

        Gameloop *obtener_partida_en_espera();
        void cerrar_gameloops_terminados();
        void eliminar_terminadas();
        void eliminar_partidas();
        void eliminar_jugadores_de_una_partida(Gameloop *partida);
        void cerrar_conexiones();
        void comenzar_partida(Gameloop *partida);
    public:
        explicit ServerLobby(int id);
        void agregar_jugador(Socket& skt);
        void finalizar();
        void run() override;
};

#endif