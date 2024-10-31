#include "cliente_sender.h"


ClienteSender::ClienteSender(ClienteProtocolo &protocolo, Queue<ComandoAccion> &queue_acciones) : protocolo(protocolo), queue_acciones(queue_acciones) {}

void ClienteSender::run(){
    while(_keep_running){
        ComandoAccion accion = queue_acciones.pop();
        try{
            if (!protocolo.enviar_accion(accion)){
                _keep_running = false;
            }

        }
        catch(const ClosedQueue &e){
            _keep_running = false;

        }
    }
    _keep_running = false;


}
      
void ClienteSender::stop(){
    _keep_running = false;
}

void ClienteSender::join(){
    Thread::join();
}

ClienteSender::~ClienteSender() {}
