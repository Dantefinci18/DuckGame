#ifndef SERVER_ACEPTADOR_H
#define SERVER_ACEPTADOR_H

#include <list>
#include <string>
#include <tuple>

#include "../common/common_queue.h"
#include "../common/common_socket.h"
#include "../common/common_thread.h"
#include "../common/common_accion.h"
#include "server_lobby.h"
#include "server_monitor.h"

class Aceptador: public Thread {
private:
    Socket& skt;
    ServerLobby lobby;

public:
    explicit Aceptador(Socket& skt);

    void run() override;
};

#endif
