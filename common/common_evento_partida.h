#ifndef COMMON_EVENTO_PARTIDA_H
#define COMMON_EVENTO_PARTIDA_H

#include <cstdint>

enum TipoEventoPartida: uint8_t{
    AGREGAR_PARTIDA,
    ELIMINAR_PARTIDA,
};

#endif