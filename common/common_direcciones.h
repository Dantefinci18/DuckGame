#ifndef COMMON_DIRECCIONES_H
#define COMMON_DIRECCIONES_H

#include "../server/Vector.h"


enum class DireccionApuntada {
    APUNTADO_ARRIBA,
    APUNTADO_DERECHA,
    APUNTADO_IZQUIERDA,
};

inline Vector obtenerDireccion(DireccionApuntada direccion) {
    switch (direccion) {
        case DireccionApuntada::APUNTADO_ARRIBA:
            return Vector(0, 1);
        case DireccionApuntada::APUNTADO_DERECHA:
            return Vector(1, 0);
        case DireccionApuntada::APUNTADO_IZQUIERDA:
            return Vector(-1, 0);
        default:
            return Vector(0, 0);
    }
}

#endif // COMMON_DIRECCIONES_H