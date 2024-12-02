#ifndef SERVER_RECEIVER_H
#define SERVER_RECEIVER_H

#include <mutex>
#include <string>
#include <tuple>
#include <utility>

#include "../common/common_queue.h"
#include "../common/common_socket.h"
#include "../common/common_thread.h"
#include "../common/common_accion.h"
#include "server_protocolo.h"

class Receiver: public Thread {
private:
    ProtocoloServidor& protocolo;
    Queue<std::shared_ptr<Accion>> *acciones;
    int id;
    std::mutex mtx;

public:
    explicit Receiver(ProtocoloServidor& protocolo, Queue<std::shared_ptr<Accion>>& acciones, int id);

    void run() override;

    bool se_cerro();

    void reset_cola(Queue<std::shared_ptr<Accion>>& comandos);
};

#endif
