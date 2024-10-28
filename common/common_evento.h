#ifndef COMMON_EVENTO_H
#define COMMON_EVENTO_H

#include <string>
#include <vector>
#include <cstdint>


struct __attribute__((__packed__)) Evento{
    uint8_t tipo;
    uint8_t id;
    uint8_t x;
    uint8_t y;
    uint8_t direccion;
};

#endif
