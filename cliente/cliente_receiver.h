#ifndef CLIENTE_RECEIVER_H
#define CLIENTE_RECEIVER_H

#include "../common/common_thread.h"
#include "cliente_protocolo.h"
#include "../common/common_queue.h"
#include <atomic>

class ClienteReceiver : public Thread{
    public:
        explicit ClienteReceiver(ClienteProtocolo &protocolo, Queue<Evento> &queue_eventos, std::atomic<bool> &cliente_conectado);
        void run() override;
    
    private:
        ClienteProtocolo &protocolo;
        Queue<Evento> &queue_eventos;
        std::atomic<bool> &cliente_conectado;


};


#endif