#include "server_servidor.h"

#include <string>

Servidor::Servidor(const char* nombre_servidor):
        skt(nombre_servidor), aceptador(comandos_acciones,monitor, skt), gameloop(comandos_acciones,monitor) {}

void Servidor::run() {
    aceptador.start();
    gameloop.start();
    std::string entrada;

    while (std::cin >> entrada, entrada != "q") {}

    gameloop.stop();
    skt.shutdown(2);
    skt.close();
    aceptador.stop();
    gameloop.join();
    aceptador.join();
}