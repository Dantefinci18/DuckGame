#include "jugador_esperando.h"

JugadorEsperando::JugadorEsperando(Socket&& skt,Queue<std::tuple<int,ComandoPartida>>& cola_comandos_partidas): 
    protocolo(std::move(skt)),
    cola_comandos_partidas(cola_comandos_partidas),
    id(generar_id()){}

void JugadorEsperando::run(){
    ComandoPartida partida = protocolo.recibir_partida();
    cola_comandos_partidas.push(std::make_tuple(id, partida));
}

int JugadorEsperando::generar_id() {
    std::random_device rd;
    std::mt19937 engine(rd());
    std::uniform_int_distribution<int> distribution(INT32_MIN, INT32_MAX);

    int id = distribution(engine);
    std::cout << id << std::endl;
    return id;
}

int JugadorEsperando::get_id(){
    return id;
}

Socket JugadorEsperando::get_socket(){
    return protocolo.get_socket();
}