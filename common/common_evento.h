#ifndef COMMON_EVENTO_H
#define COMMON_EVENTO_H

#include <string>
#include <vector>
#include <cstdint>

enum TipoEvento {
    DISPARO = 1,
    PICKUP = 2,
    SPAWN_JUGADOR = 3,
    SPAWN_OBJETO = 4,
    MOVIMIENTO_JUGADOR = 5
};

struct __attribute__((__packed__)) Evento{
    int tipo;
    int id;
    int id_2;
    float x;
    float y;

};

#endif
