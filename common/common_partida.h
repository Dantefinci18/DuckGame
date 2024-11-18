#ifndef COMMON_PARTIDA_H
#define COMMON_PARTIDA_H

#include <cstdint>

enum ComandoPartida : uint8_t{
    NUEVA_PARTIDA,
    CARGAR_PARTIDA,
    NONE_PARTIDA
};

#endif