#ifndef CLIENTE_RECEIVER_H
#define CLIENTE_RECEIVER_H

#include "../common/common_thread.h"
#include "cliente_protocolo.h"
#include "../common/common_queue.h"
#include <atomic>
#include <memory>  

class ClienteReceiver : public Thread {
public:

    /*
     * Constructor de la clase ClienteReceiver, recibe un protocolo, una cola de eventos y un atomic bool
     */
    explicit ClienteReceiver(ClienteProtocolo &protocolo, Queue<std::unique_ptr<Evento>> &queue_eventos, std::atomic<bool> &cliente_conectado);
    
    /*
     * Funcion que corre el hilo
     */
    void run() override;

    /*
     * Funcion que detiene el hilo
     */
    int get_id();

private:
    ClienteProtocolo &protocolo;
    Queue<std::unique_ptr<Evento>> &queue_eventos;  
    std::atomic<bool> &cliente_conectado;
    int id;
};

#endif
