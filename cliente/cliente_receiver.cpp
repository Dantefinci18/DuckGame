#include "cliente_receiver.h"


ClienteReceiver::ClienteReceiver(ClienteProtocolo &protocolo, Queue<Evento> &queue_eventos, std::atomic<bool> &cliente_conectado) : protocolo(protocolo), queue_eventos(queue_eventos), cliente_conectado(cliente_conectado){}

void ClienteReceiver::run(){
    Evento evento;
    while(_keep_running){
        if (protocolo.recibir_evento(evento)){
            try{
                queue_eventos.push(evento);
            }
            catch(const ClosedQueue &e){
                _keep_running = false;

        }
        }
        else{
            _keep_running = false;
        }
        
    }
    cliente_conectado = false;
    
}

void ClienteReceiver::stop(){
    _keep_running = false;
}

void ClienteReceiver::join(){
    Thread::join();
}

ClienteReceiver::~ClienteReceiver() {}