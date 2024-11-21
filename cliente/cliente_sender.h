#ifndef CLIENTE_SENDER_H
#define CLIENTE_SENDER_H

#include "../common/common_thread.h"
#include "../common/common_queue.h"
#include "../common/common_accion.h"
#include "cliente_protocolo.h"
#include <atomic>

class ClienteSender : public Thread{
    public:

        /*
         * Constructor de la clase ClienteSender, recibe un protocolo y una cola de acciones
         */
        explicit ClienteSender(ClienteProtocolo &protocolo, Queue<ComandoAccion> &queue_acciones);
        
        /*
         * Funcion que corre el hilo
         */
        void run() override;

        /*
         * Funcion que detiene el hilo
         */
        void stop() override;

        /*
         * Funcion que espera a que el hilo termine
         */
        void join() override;
        
        /*
         * Destructor de la clase ClienteSender
         */
        ~ClienteSender() ;
        
    private:
        ClienteProtocolo &protocolo;
        Queue<ComandoAccion> &queue_acciones;

        
        

};

#endif