#ifndef SERVER_SENDER_H
#define SERVER_SENDER_H

#include <mutex>
#include <string>

#include "../common/common_queue.h"
#include "../common/common_socket.h"
#include "../common/common_thread.h"
#include "../common/estado.h"
#include "server_monitor.h"
#include "server_protocolo.h"

class Sender: public Thread {
private:
    ProtocoloServidor& protocolo;
    Queue<Estado> cola_estados;
    Monitor& monitor;
    std::mutex mtx;

    void enviar_estados();

public:
    explicit Sender(ProtocoloServidor& protocolo, Monitor& monitor);

    void stop() override;

    void run() override;

    bool se_cerro();
};

#endif
