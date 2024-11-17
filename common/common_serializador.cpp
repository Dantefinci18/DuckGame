#include "common_serializador.h"
#include <bitset>
#include <iostream>
#include <cstring>
#include <memory>
#include "../server/Platform.h"
#include "../server/Player.h"
#include "../server/SpawnPlace.h"      

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
    
    if (evento.get_tipo() == Evento::TipoEvento::EventoPickup) {
        return serializar_pickup(evento);
    }
    
    if (evento.get_tipo() == Evento::TipoEvento::EventoMovimiento) {
        return serializar_movimiento(evento);
    }
    
    if (evento.get_tipo() == Evento::TipoEvento::EventoMapa) {
        return serializar_mapa(evento);
    }
}

std::vector<uint8_t> Serializador::serializar_movimiento(const Evento& evento) {
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

std::vector<uint8_t> Serializador::serializar_pickup(const Evento& evento) {
    std::vector<uint8_t> bits(136); 

    uint8_t tipo_evento = static_cast<uint8_t>(evento.get_tipo());
    for (int i = 0; i < 8; ++i) {
        bits[i] = (tipo_evento >> (7 - i)) & 1;
    }

    uint32_t x_bits;
    memcpy(&x_bits, &static_cast<const EventoPickup&>(evento).x, sizeof(float));
    for (int i = 0; i < 32; ++i) {
        bits[8 + i] = (x_bits >> (31 - i)) & 1;
    }

    // Serializar y
    uint32_t y_bits;
    memcpy(&y_bits, &static_cast<const EventoPickup&>(evento).y, sizeof(float));
    for (int i = 0; i < 32; ++i) {
        bits[40 + i] = (y_bits >> (31 - i)) & 1;
    }

    // Serializar id
    uint32_t id_bits = static_cast<uint32_t>(static_cast<const EventoPickup&>(evento).id);
    for (int i = 0; i < 32; ++i) {
        bits[72 + i] = (id_bits >> (31 - i)) & 1;
    }

    //Serializar weaponType
    uint32_t tipo_bits = static_cast<uint32_t>(static_cast<const EventoPickup&>(evento).weapon_type);
    for (int i = 0; i < 32; ++i) {
        bits[104 + i] = (tipo_bits >> (31 - i)) & 1;
    }
    return bits;
}


Evento::TipoEvento Serializador::deserializar_tipo_evento(const uint8_t* tipo_evento_data) {
    uint8_t tipo_evento_bits = 0;
    for (int i = 0; i < 8; ++i) {
        tipo_evento_bits |= (tipo_evento_data[i] << (7 - i));  
    }
    return static_cast<Evento::TipoEvento>(tipo_evento_bits);
}


std::unique_ptr<Evento> Serializador::deserializar_movimiento(const uint8_t* id_data, const uint8_t* x_data, const uint8_t* y_data) {
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


int Serializador::deserializar_cantidad(const uint8_t* cantidad_data) {
    int cantidad = 0;
    for (int i = 0; i < 32; ++i) {
        cantidad |= (cantidad_data[i] << (31 - i));
    }
    return cantidad;
}



std::vector<uint8_t> Serializador::serializar_mapa(const Evento& evento) {
    int cantidad = static_cast<const EventoMapa&>(evento).collidables.size();
    std::cout << "Cantidad de collidables: " << cantidad << std::endl;
    std::vector<uint8_t> bits(40 + cantidad * 160); 

    uint8_t tipo_evento = static_cast<uint8_t>(evento.get_tipo());
    for (int i = 0; i < 8; ++i) {
        bits[i] = (tipo_evento >> (7 - i)) & 1;
    }

    uint32_t cantidad_bits = static_cast<uint32_t>(cantidad);
    for (int i = 0; i < 32; ++i) {
        bits[8 + i] = (cantidad_bits >> (31 - i)) & 1;
    }

    const std::vector<Collidable*>& collidables = static_cast<const EventoMapa&>(evento).collidables;
    int offset = 40; 

    for (const auto& collidable : collidables) {
        uint32_t tipo_bits = static_cast<uint32_t>(collidable->getType());
        for (int i = 0; i < 32; ++i) {
            bits[offset + i] = (tipo_bits >> (31 - i)) & 1;
        }

        uint32_t x_bits;
        memcpy(&x_bits, &collidable->position.x, sizeof(float));
        for (int i = 0; i < 32; ++i) {
            bits[offset + 32 + i] = (x_bits >> (31 - i)) & 1;
        }

        uint32_t y_bits;
        memcpy(&y_bits, &collidable->position.y, sizeof(float));
        for (int i = 0; i < 32; ++i) {
            bits[offset + 64 + i] = (y_bits >> (31 - i)) & 1;
        }

        uint32_t width_bits;
        memcpy(&width_bits, &collidable->width, sizeof(float));
        for (int i = 0; i < 32; ++i) {
            bits[offset + 96 + i] = (width_bits >> (31 - i)) & 1;
        }

        uint32_t height_bits;
        memcpy(&height_bits, &collidable->height, sizeof(float));
        for (int i = 0; i < 32; ++i) {
            bits[offset + 128 + i] = (height_bits >> (31 - i)) & 1;
        }

        offset += 160; 
    }

    return bits;
}

Collidable* Serializador::deserializar_collidable(const uint8_t* collidable_data) {

    uint32_t tipo_bits = 0;
    for (int i = 0; i < 32; ++i) {
        tipo_bits |= (collidable_data[i] << (31 - i));
    }
    CollidableType tipo = static_cast<CollidableType>(tipo_bits);

    uint32_t x_bits = 0;
    for (int i = 0; i < 32; ++i) {
        x_bits |= (collidable_data[32 + i] << (31 - i));
    }
    float x;
    memcpy(&x, &x_bits, sizeof(float));

    uint32_t y_bits = 0;
    for (int i = 0; i < 32; ++i) {
        y_bits |= (collidable_data[64 + i] << (31 - i));
    }
    float y;
    memcpy(&y, &y_bits, sizeof(float));

    uint32_t width_bits = 0;
    for (int i = 0; i < 32; ++i) {
        width_bits |= (collidable_data[96 + i] << (31 - i));
    }
    float width;
    memcpy(&width, &width_bits, sizeof(float));

    uint32_t height_bits = 0;
    for (int i = 0; i < 32; ++i) {
        height_bits |= (collidable_data[128 + i] << (31 - i));
    }
    float height;
    memcpy(&height, &height_bits, sizeof(float));

    switch (tipo) {
    case CollidableType::Platform:
        return new Platform(Vector(x, y), width, height);
    case CollidableType::Player:
        return new Player(Vector(x, y));
    case CollidableType::SpawnPlace:
        return new SpawnPlace(Vector(x, y), width, height); 
    default:
        return nullptr; 
    }

    return nullptr;

    
}