#include "server_servidor.h"

#include <string>

Servidor::Servidor(const char* nombre_servidor):
        skt(nombre_servidor), aceptador(skt) {}

void Servidor::run() {
    aceptador.start();
    std::string entrada;

    while (std::cin >> entrada, entrada != "q") {}

    skt.shutdown(2);
    skt.close();
    aceptador.stop();
    aceptador.join();
}
