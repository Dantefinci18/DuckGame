#ifndef SERVER_SENDER_H
#define SERVER_SENDER_H

#include <mutex>
#include <string>

#include "../common/common_queue.h"
#include "../common/common_socket.h"
#include "../common/common_thread.h"
#include "../common/common_evento.h"
#include "../common/common_color.h"
#include "server_protocolo.h"
#include "Vector.h"

class Sender: public Thread {
private:
    ProtocoloServidor& protocolo;
    Queue<std::unique_ptr<Evento>>& cola_eventos; 
    std::mutex mtx;
    int id;
    ColorDuck color;

    void enviar_eventos();

public:
    explicit Sender(ProtocoloServidor& protocolo, Queue<std::unique_ptr<Evento>>& cola_eventos, int id,ColorDuck color);  

    void stop() override;

    void run() override;

    bool se_cerro();
};

#endif
