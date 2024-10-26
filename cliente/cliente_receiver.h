#ifndef CLIENTE_RECEIVER_H
#define CLIENTE_RECEIVER_H

#include "../common/common_thread.h"
#include "cliente_protocolo.h"
#include <atomic>

class ClienteReceiver : public Thread{
    public:
        explicit ClienteReceiver(ClienteProtocolo &protocolo);
        void run() override;
        void stop() override;
        void join() override;
        ~ClienteReceiver();
    
    private:
        ClienteProtocolo &protocolo;
        std::atomic<bool> keep_running {true};


};


#endif