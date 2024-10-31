#ifndef CLIENTE_SENDER_H
#define CLIENTE_SENDER_H

#include "../common/common_thread.h"
#include "../common/common_queue.h"
#include "../common/common_accion.h"
#include "cliente_protocolo.h"
#include <atomic>

class ClienteSender : public Thread{
    public:
        explicit ClienteSender(ClienteProtocolo &protocolo, Queue<ComandoAccion> &queue_acciones);
        void run() override;
        void stop() override;
        void join() override;
        
        ~ClienteSender() ;
        
    private:
        ClienteProtocolo &protocolo;
        Queue<ComandoAccion> &queue_acciones;

        
        

};

#endif