#ifndef COMMON_ACCION_H
#define COMMON_ACCION_H

#include <string>
#include <cstdint>

enum ComandoAccion : uint8_t{
    DERECHA,
    IZQUIERDA,
    QUIETO,
    SALTAR,
    NONE
};

#endif // COMMON_ACCION_H
