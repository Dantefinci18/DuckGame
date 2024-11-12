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

/*std::vector<uint8_t> Serializador::serializar_evento(const Evento& evento) {
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
}*/

std::vector<uint8_t> Serializador::serializar_evento(const Evento& evento) {
    std::vector<uint8_t> bits(160);

    uint32_t tipo_bits = static_cast<uint32_t>(evento.tipo);
    for (int i = 0; i < 32; ++i) {
        bits[i] = (tipo_bits >> (31 - i)) & 1;
    }

    uint32_t x_bits;
    memcpy(&x_bits, &evento.x, sizeof(float));
    for (int i = 0; i < 32; ++i) {
        bits[32 + i] = (x_bits >> (31 - i)) & 1;
    }

    uint32_t y_bits;
    memcpy(&y_bits, &evento.y, sizeof(float));
    for (int i = 0; i < 32; ++i) {
        bits[64 + i] = (y_bits >> (31 - i)) & 1;
    }

    uint32_t id_bits = static_cast<uint32_t>(evento.id);
    for (int i = 0; i < 32; ++i) {
        bits[96 + i] = (id_bits >> (31 - i)) & 1;
    }

    uint32_t id2_bits = static_cast<uint32_t>(evento.id_2);
    for (int i = 0; i < 32; ++i) {
        bits[128 + i] = (id2_bits >> (31 - i)) & 1;
    }

    std::cout << "Valor de tipo preserializar: " << evento.tipo << std::endl;
    std::cout << "Valor de x preserializar: " << evento.x << std::endl;
    std::cout << "Valor de y preserializar: " << evento.y << std::endl;
    std::cout << "Valor de id preserializar: " << evento.id << std::endl;
    std::cout << "Valor de id2 preserializar: " << evento.id_2 << std::endl;

    return bits;
}

Evento Serializador::deserializar_evento(const uint8_t* tipo_data, const uint8_t* x_data, const uint8_t* y_data, const uint8_t* id_data, const uint8_t* id2_data) {
    Evento evento;

    evento.tipo = deserializar_id(tipo_data);

    uint32_t x_bits = 0;
    for (int i = 0; i < 32; ++i) {
        x_bits |= (x_data[31 - i] << i);
    }
    memcpy(&evento.x, &x_bits, sizeof(float));

    uint32_t y_bits = 0;
    for (int i = 0; i < 32; ++i) {
        y_bits |= (y_data[31 - i] << i);
    }
    memcpy(&evento.y, &y_bits, sizeof(float));

    evento.id = deserializar_id(id_data);
    evento.id_2 = deserializar_id(id2_data);

    std::cout << "Valor de tipo deserializado: " << evento.tipo << std::endl;
    std::cout << "Valor de x deserializado: " << evento.x << std::endl;
    std::cout << "Valor de y deserializado: " << evento.y << std::endl;
    std::cout << "Valor de id deserializado: " << evento.id << std::endl;
    std::cout << "Valor de id2 deserializado: " << evento.id_2 << std::endl;

    return evento;
}

/*Evento Serializador::deserializar_evento(const uint8_t* id_data, const uint8_t* x_data, const uint8_t* y_data) {
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
}*/

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

std::vector<uint8_t> Serializador::serializar_collidable(const Collidable& collidable) {
    std::vector<uint8_t> bits(160);

    uint32_t tipo_bits = static_cast<uint32_t>(collidable.getType());
    for (int i = 0; i < 32; ++i) {
        bits[i] = (tipo_bits >> (31 - i)) & 1;
    }

    uint32_t x_bits;
    memcpy(&x_bits, &collidable.position.x, sizeof(float));
    for (int i = 0; i < 32; ++i) {
        bits[32 + i] = (x_bits >> (31 - i)) & 1;
    }

    uint32_t y_bits;
    memcpy(&y_bits, &collidable.position.y, sizeof(float));
    for (int i = 0; i < 32; ++i) {
        bits[64 + i] = (y_bits >> (31 - i)) & 1;
    }

    uint32_t width_bits;
    memcpy(&width_bits, &collidable.width, sizeof(float));
    for (int i = 0; i < 32; ++i) {
        bits[96 + i] = (width_bits >> (31 - i)) & 1;
    }

    uint32_t height_bits;
    memcpy(&height_bits, &collidable.height, sizeof(float));
    for (int i = 0; i < 32; ++i) {
        bits[128 + i] = (height_bits >> (31 - i)) & 1;
    }

    return bits;
}

Collidable* Serializador::deserializar_collidable(const uint8_t* collidable_data) {

    uint32_t tipo_bits = 0;
    for (int i = 0; i < 32; i++) {
        tipo_bits |= (collidable_data[i] << (31 - i));
    }
    CollidableType tipo = static_cast<CollidableType>(tipo_bits);

    uint32_t x_bits = 0;
    for (int i = 0; i < 32; i++) {
        x_bits |= (collidable_data[32 + i] << (31 - i));
    }
    float x;
    memcpy(&x, &x_bits, sizeof(float));

    uint32_t y_bits = 0;
    for (int i = 0; i < 32; i++) {
        y_bits |= (collidable_data[64 + i] << (31 - i));
    }
    float y;
    memcpy(&y, &y_bits, sizeof(float));

    uint32_t width_bits = 0;
    for (int i = 0; i < 32; i++) {
        width_bits |= (collidable_data[96 + i] << (31 - i));
    }
    float width;
    memcpy(&width, &width_bits, sizeof(float));

    uint32_t height_bits = 0;
    for (int i = 0; i < 32; i++) {
        height_bits |= (collidable_data[128 + i] << (31 - i));
    }
    float height;
    memcpy(&height, &height_bits, sizeof(float));

    Vector position(x, y);

    if (tipo == CollidableType::Platform) {
        return new Platform(position, width, height);
    } else if (tipo == CollidableType::Player) {
        return new Player(position);
    }

    return nullptr;
}
