#include "cliente_sender.h"


ClienteSender::ClienteSender(ClienteProtocolo &protocolo) : protocolo(protocolo) {}

void ClienteSender::run(){
    while(keep_running){
       // protocolo.enviar_comando();
    }
}

ClienteSender::~ClienteSender() {}
