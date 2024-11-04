#include "cliente_receiver.h"


ClienteReceiver::ClienteReceiver(ClienteProtocolo &protocolo, Queue<Evento> &queue_eventos, std::atomic<bool> &cliente_conectado) : protocolo(protocolo), queue_eventos(queue_eventos), cliente_conectado(cliente_conectado), id(-1){}

void ClienteReceiver::run(){
    Evento evento;
    id = protocolo.recibir_id();
    std::cout << "id for client" << id << std::endl;
    while(_keep_running){
        try{
            if (protocolo.recibir_evento(evento)){
                queue_eventos.push(evento);
            }
            else{
                _keep_running = false;
            }
        }catch(std::exception &e){
            if (_keep_running)
                std::cerr << "Error: " << e.what() << "\n";

        }
        
    }
    cliente_conectado = false;
    
}

int ClienteReceiver::get_id() {
    return id;
}