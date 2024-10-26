#include "cliente_receiver.h"

ClienteReceiver::ClienteReceiver(ClienteProtocolo &protocolo) : protocolo(protocolo) {}

void ClienteReceiver::run(){
    while(keep_running){
        // Estado estado = protocolo.recibir_estado();
    }
}

void ClienteReceiver::stop(){
    keep_running = false;
}

void ClienteReceiver::join(){
    Thread::join();
}

ClienteReceiver::~ClienteReceiver() {}