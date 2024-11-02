#include "common_serializador.h"
#include <bitset>
#include <iostream>
#include <cstring>

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
    std::vector<uint8_t> bits(96); 

    // Serializar x
    uint32_t x_bits;
    memcpy(&x_bits, &evento.x, sizeof(float));  
    for (int i = 0; i < 32; ++i) {
        bits[i] = (x_bits >> (31 - i)) & 1;
    }

    // Serializar y
    uint32_t y_bits;
    memcpy(&y_bits, &evento.y, sizeof(float));
    for (int i = 0; i < 32; ++i) {
        bits[32 + i] = (y_bits >> (31 - i)) & 1; 
    }

    // Serializar id
    uint32_t id_bits = static_cast<uint32_t>(evento.id);
    for (int i = 0; i < 32; ++i) {
        bits[64 + i] = (id_bits >> (31 - i)) & 1; 
    }

    std::cout << "Valor de x preserializar: " << evento.x << std::endl;
    std::cout << "Valor de y preserializar: " << evento.y << std::endl;
    std::cout << "Valor de id preserializar: " << evento.id << std::endl;
    return bits; 
}

Evento Serializador::deserializar_evento(const uint8_t* id_data, const uint8_t* x_data, const uint8_t* y_data) {
    Evento evento; 
    // Deserializar x
    uint32_t x_bits = 0;
    for (int i = 0; i < 32; ++i) {
        x_bits |= (x_data[31 - i] << i);  
    }
    memcpy(&evento.x, &x_bits, sizeof(float)); 

    // Deserializar y
    uint32_t y_bits = 0;
    for (int i = 0; i < 32; ++i) {
        y_bits |= (y_data[31 - i] << i);  
    }
    memcpy(&evento.y, &y_bits, sizeof(float));  
    evento.id = deserializar_id(id_data);

    std::cout << "Valor de x deserializado: " << evento.x << std::endl;
    std::cout << "Valor de y deserializado: " << evento.y << std::endl;
    std::cout << "Valor de id deserializado: " << evento.id << std::endl;
    return evento; 
}

std::vector<uint8_t> Serializador::serializar_id(int id) {
    std::vector<uint8_t> binary_bits;

    uint32_t id_bits = static_cast<uint32_t>(id);
    for (int i = 0; i < 32; ++i) {
        binary_bits.push_back((id_bits >> (31 - i)) & 1);
    }

    return binary_bits;
}

int Serializador::deserializar_id(const uint8_t* id_binary) {
    int result = 0;
    for (size_t i = 0; i < 32; ++i) {
        result = (result << 1) | id_binary[i];
    }
    return result;
}

void Serializador::imprimir_uint8_t_array(const uint8_t* array, size_t size) {
    for (size_t i = 0; i < size; ++i) {
        std::cout << static_cast<int>(array[i]); // Convertir a int para evitar impresión como char
    }
    std::cout<<std::endl;
}