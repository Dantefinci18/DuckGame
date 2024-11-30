#include "common_serializador.h"
#include <bitset>
#include <iostream>
#include <cstring>
#include <memory>
      
std::vector<uint8_t> Serializador::serializar_enum(std::bitset<8> bits){
    std::vector<uint8_t> buffer(8); 
    for (int i = 0; i < 8; ++i) {
        buffer[7 - i] = bits[i] ? 1 : 0;  
    }

    return buffer;
}

std::vector<uint8_t> Serializador::serializar_accion(ComandoAccion &accion) {
    std::bitset<8> bits(accion);  
    return serializar_enum(bits);
}

uint8_t Serializador::deserializar_enum(const uint8_t* data){
    uint8_t valor = 0;
    
    for (int i = 0; i < 8; ++i) {
        valor |= (data[7 - i] << i);
    }

    return valor;
}


ComandoAccion Serializador::deserializar_accion(const uint8_t* data) {
    ComandoAccion accion = static_cast<ComandoAccion>(deserializar_enum(data));
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
    
    if (evento.get_tipo() == Evento::TipoEvento::EventoSpawnArma) {
        return serializar_spawn_arma(evento);
    }

    if (evento.get_tipo() == Evento::TipoEvento::EventoDisparo){
        return serializar_disparo(evento);
    }

    if (evento.get_tipo() == Evento::TipoEvento::EventoMuerte){
        return serializar_muerte(evento);
    }

    if (evento.get_tipo() == Evento::TipoEvento::EventoApuntar){
        return serializar_apuntar(evento);
    }

    if (evento.get_tipo() == Evento::TipoEvento::EventoEspera){ 
        std::vector<uint8_t> buffer = serializar_espera(Evento::TipoEvento::EventoEspera);
        imprimir_uint8_t_array(buffer.data(),buffer.size());
        return buffer;
    }

    if (evento.get_tipo() == Evento::TipoEvento::EventoAgacharse){
        return serializar_agacharse(evento);
    }

    if (evento.get_tipo() == Evento::TipoEvento::EventoLevantarse){
        return serializar_levantarse(evento);
    }

    if (evento.get_tipo() == Evento::TipoEvento::EventoWinRound) {
        return serializar_win_round(evento);
    }

    if (evento.get_tipo() == Evento::TipoEvento::EventoWinMatch) {
        return serializar_win_round(evento);
    }
    
    if (evento.get_tipo() == Evento::TipoEvento::EventoBala){
        return serializar_bala(evento);
    }

    if (evento.get_tipo() == Evento::TipoEvento::EventoCajaDestruida){
        return serializar_caja_destruida(evento);
    }

    if (evento.get_tipo() == Evento::TipoEvento::EventoSpawnArmaBox){
        return serializar_spawn_arma_box(evento);
    }
    return std::vector<uint8_t>();
}

std::vector<uint8_t> Serializador::serializar_espera(const Evento::TipoEvento& tipo_evento){

    std::vector<uint8_t> buffer(8);  

    uint8_t tipo = static_cast<uint8_t>(tipo_evento);
    for (int i = 0; i < 8; ++i) {
        buffer[i] = (tipo >> (7 - i)) & 1;
    }

    return buffer;
    
}

std::vector<uint8_t> Serializador::serializar_movimiento(const Evento& evento) {
    std::vector<uint8_t> bits(114); 
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

    // Serializar color 
    uint8_t color_bits = static_cast<uint8_t>(static_cast<const EventoMovimiento&>(evento).color);
    for (int i = 0; i < 8; ++i) {
        bits[104 + i] = (color_bits >> (7 - i)) & 1;
    }

    char is_flapping = static_cast<char>(static_cast<const EventoMovimiento&>(evento).is_flapping);
    bits[112] = is_flapping; 

    char reset = static_cast<char>(static_cast<const EventoMovimiento&>(evento).reset);
    bits[113] = reset; 
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
    //imprimir_uint8_t_array(bits.data(), 136);
    return bits;
}

std::vector<uint8_t> Serializador::serializar_spawn_arma(const Evento& evento) {
    std::vector<uint8_t> bits(104); 

    uint8_t tipo_evento = static_cast<uint8_t>(evento.get_tipo());
    for (int i = 0; i < 8; ++i) {
        bits[i] = (tipo_evento >> (7 - i)) & 1;
    }

    uint32_t x_bits;
    memcpy(&x_bits, &static_cast<const EventoSpawnArma&>(evento).x, sizeof(float));
    for (int i = 0; i < 32; ++i) {
        bits[8 + i] = (x_bits >> (31 - i)) & 1;
    }

    // Serializar y
    uint32_t y_bits;
    memcpy(&y_bits, &static_cast<const EventoSpawnArma&>(evento).y, sizeof(float));
    for (int i = 0; i < 32; ++i) {
        bits[40 + i] = (y_bits >> (31 - i)) & 1;
    }

    //Serializar weaponType
    uint32_t tipo_bits = static_cast<uint32_t>(static_cast<const EventoSpawnArma&>(evento).weapon_type);
    for (int i = 0; i < 32; ++i) {
        bits[72 + i] = (tipo_bits >> (31 - i)) & 1;
    }
    //imprimir_uint8_t_array(bits.data(), 104);
    return bits;
}

std::vector<uint8_t> Serializador::serializar_spawn_arma_box(const Evento& evento) {
    std::vector<uint8_t> bits(168); 

    uint8_t tipo_evento = static_cast<uint8_t>(evento.get_tipo());
    for (int i = 0; i < 8; ++i) {
        bits[i] = (tipo_evento >> (7 - i)) & 1;
    }

    uint32_t x_bits;
    memcpy(&x_bits, &static_cast<const EventoSpawnArmaBox&>(evento).x, sizeof(float));
    for (int i = 0; i < 32; ++i) {
        bits[8 + i] = (x_bits >> (31 - i)) & 1;
    }

    // Serializar y
    uint32_t y_bits;
    memcpy(&y_bits, &static_cast<const EventoSpawnArmaBox&>(evento).y, sizeof(float));
    for (int i = 0; i < 32; ++i) {
        bits[40 + i] = (y_bits >> (31 - i)) & 1;
    }

    // Serializar width
    uint32_t width_bits = static_cast<uint32_t>(static_cast<const EventoSpawnArmaBox&>(evento).width);
    for (int i = 0; i < 32; ++i) {
        bits[72 + i] = (width_bits >> (31 - i)) & 1;
    }

    // Serializar height
    uint32_t height_bits = static_cast<uint32_t>(static_cast<const EventoSpawnArmaBox&>(evento).height);
    for (int i = 0; i < 32; ++i) {
        bits[104 + i] = (height_bits >> (31 - i)) & 1;
    }

    //Serializar weaponType
    uint32_t tipo_bits = static_cast<uint32_t>(static_cast<const EventoSpawnArmaBox&>(evento).weapon_type);
    for (int i = 0; i < 32; ++i) {
        bits[136 + i] = (tipo_bits >> (31 - i)) & 1;
    }
    //imprimir_uint8_t_array(bits.data(), 104);
    return bits;
}

std::vector<uint8_t> Serializador::serializar_disparo(const Evento& evento) {
    std::vector<uint8_t> bits(40);

    uint8_t tipo_evento = static_cast<uint8_t>(evento.get_tipo());
    for (int i = 0; i < 8; ++i) {
        bits[i] = (tipo_evento >> (7 - i)) & 1;
    }

    uint32_t id_bits = static_cast<uint32_t>(static_cast<const EventoDisparo&>(evento).id);
    for (int i = 0; i < 32; ++i) {
        bits[8 + i] = (id_bits >> (31 - i)) & 1;
    }

    return bits;
}

std::vector<uint8_t> Serializador::serializar_muerte(const Evento& evento) {
    std::vector<uint8_t> bits(40);

    uint8_t tipo_evento = static_cast<uint8_t>(evento.get_tipo());
    for (int i = 0; i < 8; ++i) {
        bits[i] = (tipo_evento >> (7 - i)) & 1;
    }

    uint32_t id_bits = static_cast<uint32_t>(static_cast<const EventoMuerte&>(evento).id);
    for (int i = 0; i < 32; ++i) {
        bits[8 + i] = (id_bits >> (31 - i)) & 1;
    }

    return bits;
}

std::vector<uint8_t> Serializador::serializar_apuntar(const Evento& evento) {
    std::vector<uint8_t> bits(48);

    uint8_t tipo_evento = static_cast<uint8_t>(evento.get_tipo());
    for (int i = 0; i < 8; ++i) {
        bits[i] = (tipo_evento >> (7 - i)) & 1;
    }

    uint32_t id_bits = static_cast<uint32_t>(static_cast<const EventoApuntar&>(evento).id);
    for (int i = 0; i < 32; ++i) {
        bits[8 + i] = (id_bits >> (31 - i)) & 1;
    }

    uint8_t direccion_bits = static_cast<uint8_t>(static_cast<const EventoApuntar&>(evento).direccion);
    for (int i = 0; i < 8; ++i) {
        bits[40 + i] = (direccion_bits >> (7 - i)) & 1;
    }

    return bits;
}

std::vector<uint8_t> Serializador::serializar_agacharse(const Evento& evento) {
    std::vector<uint8_t> bits(40);

    uint8_t tipo_evento = static_cast<uint8_t>(evento.get_tipo());
    for (int i = 0; i < 8; ++i) {
        bits[i] = (tipo_evento >> (7 - i)) & 1;
    }

    uint32_t id_bits = static_cast<uint32_t>(static_cast<const EventoAgacharse&>(evento).id);
    for (int i = 0; i < 32; ++i) {
        bits[8 + i] = (id_bits >> (31 - i)) & 1;
    }

    return bits;
}

std::vector<uint8_t> Serializador::serializar_levantarse(const Evento& evento) {
    std::vector<uint8_t> bits(40);

    uint8_t tipo_evento = static_cast<uint8_t>(evento.get_tipo());
    for (int i = 0; i < 8; ++i) {
        bits[i] = (tipo_evento >> (7 - i)) & 1;
    }

    uint32_t id_bits = static_cast<uint32_t>(static_cast<const EventoLevantarse&>(evento).id);
    for (int i = 0; i < 32; ++i) {
        bits[8 + i] = (id_bits >> (31 - i)) & 1;
    }

    return bits;
}

std::vector<uint8_t> Serializador::serializar_win_round(const Evento& evento) {
    std::vector<uint8_t> bits(40);

    uint8_t tipo_evento = static_cast<uint8_t>(evento.get_tipo());
    for (int i = 0; i < 8; ++i) {
        bits[i] = (tipo_evento >> (7 - i)) & 1;
    }

    uint32_t id_bits = static_cast<uint32_t>(static_cast<const EventoWinRound&>(evento).id);
    for (int i = 0; i < 32; ++i) {
        bits[8 + i] = (id_bits >> (31 - i)) & 1;
    }

    return bits;
}

std::vector<uint8_t> Serializador::serializar_bala(const Evento& evento) {
    std::vector<uint8_t> bits(72);

    uint8_t tipo_evento = static_cast<uint8_t>(evento.get_tipo());
    for (int i = 0; i < 8; ++i) {
        bits[i] = (tipo_evento >> (7 - i)) & 1;
    }

    uint32_t x_bits;
    memcpy(&x_bits, &static_cast<const EventoBala&>(evento).x, sizeof(float));
    for (int i = 0; i < 32; ++i) {
        bits[8 + i] = (x_bits >> (31 - i)) & 1;
    }

    uint32_t y_bits;
    memcpy(&y_bits, &static_cast<const EventoBala&>(evento).y, sizeof(float));
    for (int i = 0; i < 32; ++i) {
        bits[40 + i] = (y_bits >> (31 - i)) & 1;
    }
    

    return bits;
}

std::vector<uint8_t> Serializador::serializar_caja_destruida(const Evento& evento) {
    std::vector<uint8_t> bits(72);

    uint8_t tipo_evento = static_cast<uint8_t>(evento.get_tipo());
    for (int i = 0; i < 8; ++i) {
        bits[i] = (tipo_evento >> (7 - i)) & 1;
    }

    uint32_t x_bits;
    memcpy(&x_bits, &static_cast<const EventoCajaDestruida&>(evento).x, sizeof(float));
    for (int i = 0; i < 32; ++i) {
        bits[8 + i] = (x_bits >> (31 - i)) & 1;
    }

    uint32_t y_bits;
    memcpy(&y_bits, &static_cast<const EventoCajaDestruida&>(evento).y, sizeof(float));
    for (int i = 0; i < 32; ++i) {
        bits[40 + i] = (y_bits >> (31 - i)) & 1;
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


std::unique_ptr<Evento> Serializador::deserializar_movimiento(
    const uint8_t* id_data, const uint8_t* color_data, const uint8_t* x_data, const uint8_t* y_data, char is_flapping, char reset) {
    int id;
    float x, y;

    uint32_t id_bits = 0;
    for (int i = 0; i < 32; ++i) {
        id_bits |= (id_data[i] << (31 - i));
    }
    id = static_cast<int>(id_bits);

    uint8_t color_bits = 0;
    for (int i = 0; i < 8; ++i) {
        color_bits |= (color_data[i] << (7 - i));
    }
    ColorDuck color_asignado = static_cast<ColorDuck>(color_bits);

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

    return std::make_unique<EventoMovimiento>(id, color_asignado, x, y, is_flapping, reset);
}


std::unique_ptr<Evento> Serializador::deserializar_pickup(const uint8_t* id_data, const uint8_t* x_data, const uint8_t* y_data, const uint8_t* weapon_type_data) {
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

    uint32_t tipo_bits = 0;
    for (int i = 0; i < 32; ++i) {
        tipo_bits |= (weapon_type_data[i] << (31 - i));
    }
    WeaponType tipo = static_cast<WeaponType>(tipo_bits);
    return std::make_unique<EventoPickup>(id, x, y, tipo);
}

std::unique_ptr<Evento> Serializador::deserializar_spawn_arma(const uint8_t* x_data, const uint8_t* y_data, const uint8_t* weapon_type_data) {
    float x, y;

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

    uint32_t tipo_bits = 0;
    for (int i = 0; i < 32; ++i) {
        tipo_bits |= (weapon_type_data[i] << (31 - i));
    }
    WeaponType tipo = static_cast<WeaponType>(tipo_bits);
    return std::make_unique<EventoSpawnArma>(x, y, tipo);
}

std::unique_ptr<Evento> Serializador::deserializar_spawn_arma_box(const uint8_t* x_data, const uint8_t* y_data, 
    const uint8_t* width_data, const uint8_t* height_data, const uint8_t* weapon_type_data) {
    float x, y;

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

    uint32_t tipo_bits = 0;
    for (int i = 0; i < 32; ++i) {
        tipo_bits |= (weapon_type_data[i] << (31 - i));
    }

    uint32_t width = 0;
    for (int i = 0; i < 32; ++i) {
        width |= (width_data[i] << (31 - i));
    }

    uint32_t height = 0;
    for (int i = 0; i < 32; ++i) {
        height |= (height_data[i] << (31 - i));
    }
    WeaponType tipo = static_cast<WeaponType>(tipo_bits);
    return std::make_unique<EventoSpawnArmaBox>(x, y, width, height, tipo);
}

std::unique_ptr<Evento> Serializador::deserializar_disparo(const uint8_t* id_data) {
    uint32_t id_bits = 0;

    for (int i = 0; i < 32; ++i) {
        id_bits |= (id_data[i] << (31 - i));
    }
    int id = static_cast<int>(id_bits);

    return std::make_unique<EventoDisparo>(id);
}

std::unique_ptr<Evento> Serializador::deserializar_muerte(const uint8_t* id_data) {
    uint32_t id_bits = 0;

    for (int i = 0; i < 32; ++i) {
        id_bits |= (id_data[i] << (31 - i));
    }
    int id = static_cast<int>(id_bits);

    return std::make_unique<EventoMuerte>(id);
}

std::unique_ptr<Evento> Serializador::deserializar_apuntar(const uint8_t* id_data, const uint8_t* direccion_data) {
    uint32_t id_bits = 0;
    for (int i = 0; i < 32; ++i) {
        id_bits |= (id_data[i] << (31 - i));
    }
    int id = static_cast<int>(id_bits);

    uint32_t direccion_bits = 0;
    for (int i = 0; i < 8; ++i) {
        direccion_bits |= (direccion_data[i] << (7 - i));
    }
    DireccionApuntada direccion = static_cast<DireccionApuntada>(direccion_bits);

    return std::make_unique<EventoApuntar>(id, direccion);
}
std::unique_ptr<Evento> Serializador::deserializar_bala(const uint8_t* x_data, const uint8_t* y_data) {
    float x, y;

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

    return std::make_unique<EventoBala>(x, y);
}

std::unique_ptr<Evento> Serializador::deserializar_caja_destruida(const uint8_t* x_data, const uint8_t* y_data) {
    float x, y;

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

    return std::make_unique<EventoCajaDestruida>(x, y);
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

    // Serialize leaderboard
    const Leaderboard& leaderboard = static_cast<const EventoMapa&>(evento).leaderboard;

    // Serialize leaderboard basic fields
    std::vector<uint8_t> leaderboard_bits(64); // 3 fields * 32 bits each
    uint32_t round = leaderboard.round;
    for (int i = 0; i < 32; ++i) {
        leaderboard_bits[i] = (round >> (31 - i)) & 1;
    }

    uint32_t set_of_rounds = leaderboard.set_of_rounds;
    for (int i = 0; i < 32; ++i) {
        leaderboard_bits[32 + i] = (set_of_rounds >> (31 - i)) & 1;
    }

    bits.insert(bits.end(), leaderboard_bits.begin(), leaderboard_bits.end());

    // Serialize player_rounds_won
    std::unordered_map<int,int> player_rounds_won = leaderboard.player_rounds_won;
    uint32_t map_size = static_cast<uint32_t>(player_rounds_won.size());
    std::vector<uint8_t> map_bits(32 + map_size * 64); // 32 for size, 64 for each entry (32 key + 32 value)

    for (int i = 0; i < 32; ++i) {
        map_bits[i] = (map_size >> (31 - i)) & 1;
    }

    int map_offset = 32;
    for (const auto& [player_id, rounds_won] : player_rounds_won) {
        uint32_t player_bits = static_cast<uint32_t>(player_id);
        for (int i = 0; i < 32; ++i) {
            map_bits[map_offset + i] = (player_bits >> (31 - i)) & 1;
        }

        uint32_t rounds_bits = static_cast<uint32_t>(rounds_won);
        for (int i = 0; i < 32; ++i) {
            map_bits[map_offset + 32 + i] = (rounds_bits >> (31 - i)) & 1;
        }

        map_offset += 64;
    }

    bits.insert(bits.end(), map_bits.begin(), map_bits.end());
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
    case CollidableType::SpawnPlace:
        return new SpawnPlace(Vector(x, y), width, height); 
    case CollidableType::Box:
        return new Box(Vector(x, y), width, height);
    default:
        return nullptr; 
    }

    return nullptr;   
}

std::tuple<int, int> Serializador::deserializar_tuple64(const uint8_t* tuple_data) {
    uint32_t value1 = 0;
    for (int i = 0; i < 32; ++i) {
        value1 |= (tuple_data[i] << (31 - i));
    }

    uint32_t value2 = 0;
    for (int i = 0; i < 32; ++i) {
        value2 |= (tuple_data[i + 32] << (31 - i));
    }
    return std::make_tuple<int,int>(value1, value2);
}