#ifndef CLIENTE_SENDER_H
#define CLIENTE_SENDER_H

#include "../common/common_thread.h"
#include "cliente_protocolo.h"
#include <atomic>

class ClienteSender : public Thread{
    public:
        explicit ClienteSender(ClienteProtocolo &protocolo);
        void run() override;
        
        ~ClienteSender() ;
        
    private:
        ClienteProtocolo &protocolo;
        std::atomic<bool> keep_running;

        
        

};

#endif