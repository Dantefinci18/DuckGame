#include "server_servidor.h"

#include <string>

Servidor::Servidor(const char* nombre_servidor):
        skt(nombre_servidor), aceptador(comandos_acciones,monitor, skt), gameloop(comandos_acciones,monitor) {}

void Servidor::run() {
    Platform platform({100.0f, 40.0f}, 100.0, 30.0);
    gameloop.agregar_plataforma(platform);
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
