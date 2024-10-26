#include "cliente.h"

Cliente::Cliente(const char* hostname, const char* servname) : protocolo(hostname, servname), receiver(protocolo),sender(protocolo) {}

void Cliente::start(){
    receiver.run();
    sender.run();

   
}

void Cliente::stop(){
    receiver.stop();
    sender.stop();
}

void Cliente::join(){
    receiver.join();
    sender.join();
}

Cliente::~Cliente(){}