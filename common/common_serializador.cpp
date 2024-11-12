#include "common_serializador.h"
#include <bitset>
#include <iostream>
#include <cstring>
#include <memory>

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
    std::vector<uint8_t> bits(104); 

    uint8_t tipo_evento = static_cast<uint8_t>(evento.get_tipo());
    for (int i = 0; i < 8; ++i) {
        bits[i] = (tipo_evento >> (7 - i)) & 1;
    }

    uint32_t x_bits;
    memcpy(&x_bits, &static_cast<const EventoMovimiento&>(evento).x, sizeof(float));
    for (int i = 0; i < 32; ++i) {
        bits[8 + i] = (x_bits >> (31 - i)) & 1;
    }

    // Serializar y
    uint32_t y_bits;
    memcpy(&y_bits, &static_cast<const EventoMovimiento&>(evento).y, sizeof(float));
    for (int i = 0; i < 32; ++i) {
        bits[40 + i] = (y_bits >> (31 - i)) & 1;
    }

    // Serializar id
    uint32_t id_bits = static_cast<uint32_t>(static_cast<const EventoMovimiento&>(evento).id);
    for (int i = 0; i < 32; ++i) {
        bits[72 + i] = (id_bits >> (31 - i)) & 1;
    }

    return bits;
}



std::unique_ptr<Evento> Serializador::deserializar_evento(const uint8_t* tipo_evento_data, const uint8_t* id_data, const uint8_t* x_data, const uint8_t* y_data) {
    uint8_t tipo_evento_bits = 0;
    for (int i = 0; i < 8; ++i) {
        tipo_evento_bits |= (tipo_evento_data[i] << (7 - i));  
    }
    Evento::TipoEvento tipo_evento = static_cast<Evento::TipoEvento>(tipo_evento_bits);

    if (tipo_evento == Evento::EventoMovimiento) {
        int id;
        float x, y;

        uint32_t id_bits = 0;
        for (int i = 0; i < 32; ++i) {
            id_bits |= (id_data[i] << (31 - i));
        }
        id = static_cast<int>(id_bits);

        uint32_t x_bits = 0;
        for (int i = 0; i < 32; ++i) {
            x_bits |= (x_data[i] << (31 - i));
        }
        memcpy(&x, &x_bits, sizeof(float));

        uint32_t y_bits = 0;
        for (int i = 0; i < 32; ++i) {
            y_bits |= (y_data[i] << (31 - i));
        }
        memcpy(&y, &y_bits, sizeof(float));

        return std::make_unique<EventoMovimiento>(id, x, y);
    }

    return nullptr;
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
        std::cout << static_cast<int>(array[i]);
    }
    std::cout<<std::endl;
}