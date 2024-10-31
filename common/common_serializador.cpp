#include "common_serializador.h"
#include <bitset>
#include <iostream>

std::vector<uint8_t> Serializador::serializar_accion(ComandoAccion &accion) {
    std::bitset<8> bits(accion);  

    std::vector<uint8_t> buffer(8); 
    for (int i = 0; i < 8; ++i) {
        buffer[7 - i] = bits[i] ? 1 : 0;  
    }

    return buffer;
}


ComandoAccion Serializador::deserializar_accion(const uint8_t* data) {
    uint8_t accion_valor = 0;
    for (int i = 0; i < 8; ++i) {
        accion_valor |= (data[7 - i] << i);
    }


    ComandoAccion accion = static_cast<ComandoAccion>(accion_valor);
    return accion;
}

std::vector<uint8_t> Serializador::serializar_evento(const Evento& evento) {
    std::vector<uint8_t> bits(64); 

    uint32_t x_bits = *reinterpret_cast<const uint32_t*>(&evento.x);
    for (int i = 0; i < 32; ++i) {
        bits[i] = (x_bits >> (31 - i)) & 1;
    }

    uint32_t y_bits = *reinterpret_cast<const uint32_t*>(&evento.y);
    for (int i = 0; i < 32; ++i) {
        bits[32 + i] = (y_bits >> (31 - i)) & 1; 
    }

    return bits; 
}


Evento Serializador::deserializar_evento(const uint8_t* x_data, const uint8_t* y_data) {
    Evento evento; 

    uint32_t x_bits = 0;
    for (int i = 0; i < 32; ++i) {
        x_bits |= (x_data[31 - i] << i);  
    }
    evento.x = *reinterpret_cast<float*>(&x_bits); 

    uint32_t y_bits = 0;
    for (int i = 0; i < 32; ++i) {
        y_bits |= (y_data[31 - i] << i);  
    }
    evento.y = *reinterpret_cast<float*>(&y_bits);

    std::cout << "Valor de x deserializado: " << evento.x << std::endl;
    std::cout << "Valor de y deserializado: " << evento.y << std::endl;

    return evento; 
}