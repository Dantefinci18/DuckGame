#include "common_serializador.h"
#include <bitset>
#include <iostream>
#include <cstring>
#include <memory>
      
std::vector<uint8_t> Serializador::serializar_enum(std::bitset<5> bits){
    std::vector<uint8_t> buffer(5); 
    for (int i = 0; i < 5; ++i) {
        buffer[i] = bits[i];
    }

    return buffer;
}

std::vector<uint8_t> Serializador::serializar_accion(ComandoAccion &accion) {
    std::bitset<5> bits(accion);  
    return serializar_enum(bits);
}

uint8_t Serializador::deserializar_enum(const uint8_t* data){
    uint8_t valor = 0;
    
    std::bitset<5> bits;
    for (int i = 0; i  < 5  ; i++) {
        bits[i] = data[i];
    }
    valor = static_cast<uint8_t>(bits.to_ulong());
    
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

    if (evento.get_tipo() == Evento::TipoEvento::EventoPickupProteccion) {
        return serializar_pickup_proteccion(evento);
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

    if (evento.get_tipo() == Evento::TipoEvento::EventoMuerte){
        return serializar_muerte(evento);
    }

    if (evento.get_tipo() == Evento::TipoEvento::EventoApuntar){
        return serializar_apuntar(evento);
    }

    if (evento.get_tipo() == Evento::TipoEvento::EventoEspera){ 
        return serializar_espera(Evento::TipoEvento::EventoEspera);
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

    if (evento.get_tipo() == Evento::TipoEvento::EventoSpawnProteccionBox){
        return serializar_spawn_proteccion_box(evento);
    }
    if (evento.get_tipo() == Evento::TipoEvento::EventoDisparo){
        return serializar_espera(Evento::TipoEvento::EventoDisparo);
    }

    return std::vector<uint8_t>();
}

std::vector<uint8_t> Serializador::serializar_espera(const Evento::TipoEvento& tipo_evento){

    std::vector<uint8_t> buffer(8);  

    uint8_t tipo = static_cast<uint8_t>(tipo_evento);
    serializar_tipo_evento(buffer, tipo, 0);
    return buffer;
    
}



std::vector<uint8_t> Serializador::serializar_movimiento(const Evento& evento) {
    std::vector<uint8_t> bits(54);

    uint8_t tipo_evento = static_cast<uint8_t>(evento.get_tipo());

    serializar_tipo_evento(bits, tipo_evento, 0);  
    uint32_t id = static_cast<uint32_t>(static_cast<const EventoMovimiento&>(evento).id);
    serializar_id_dos(bits, id, 8);

    int x = static_cast<int>(static_cast<const EventoMovimiento&>(evento).x);
    int y = static_cast<int>(static_cast<const EventoMovimiento&>(evento).y);
    serializar_coordenadas(bits, x, y, 24, 36);

    
    uint8_t color = static_cast<uint8_t>(static_cast<const EventoMovimiento&>(evento).color);
    serializar_color(bits, color, 48);

    char is_flapping = static_cast<char>(static_cast<const EventoMovimiento&>(evento).is_flapping);
    bits[52] = is_flapping;

    char reset = static_cast<char>(static_cast<const EventoMovimiento&>(evento).reset);
    bits[53] = reset;

    return bits;
}


std::vector<uint8_t> Serializador::serializar_pickup(const Evento& evento) {
    std::vector<uint8_t> bits(52);  

    uint8_t tipo_evento = static_cast<uint8_t>(evento.get_tipo());
    serializar_tipo_evento(bits, tipo_evento, 0);  

    int id = static_cast<int>(static_cast<const EventoPickup&>(evento).id);
    serializar_id_dos(bits, id, 8);

    int x = static_cast<int>(static_cast<const EventoPickup&>(evento).x);
    int y = static_cast<int>(static_cast<const EventoPickup&>(evento).y);
    serializar_coordenadas(bits, x, y, 24, 36);
    
    uint8_t weapon_type = static_cast<uint8_t>(static_cast<const EventoPickup&>(evento).weapon_type);
    serializar_weapon_type(bits, weapon_type, 48); 

    return bits;
}

std::vector<uint8_t> Serializador::serializar_pickup_proteccion(const Evento& evento) {
    std::vector<uint8_t> bits(49); 

    uint8_t tipo_evento = static_cast<uint8_t>(evento.get_tipo());
    serializar_tipo_evento(bits, tipo_evento, 0);

    int id = static_cast<int>(static_cast<const EventoPickupProteccion&>(evento).id);
    serializar_id_dos(bits, id, 8);

    int x = static_cast<int>(static_cast<const EventoPickupProteccion&>(evento).x);
    int y = static_cast<int>(static_cast<const EventoPickupProteccion&>(evento).y);
    serializar_coordenadas(bits, x, y, 24, 36);

    uint8_t proteccion_type = static_cast<uint8_t>(static_cast<const EventoPickupProteccion&>(evento).proteccion_type);
    bits[48] = proteccion_type;
    return bits;
}



std::vector<uint8_t> Serializador::serializar_spawn_arma(const Evento& evento) {
    std::vector<uint8_t> bits(36); 

    uint8_t tipo_evento = static_cast<uint8_t>(evento.get_tipo());
    serializar_tipo_evento(bits, tipo_evento, 0);

    int x = static_cast<int>(static_cast<const EventoSpawnArma&>(evento).x);
    int y = static_cast<int>(static_cast<const EventoSpawnArma&>(evento).y);

    serializar_coordenadas(bits, x, y, 8, 20);

    uint32_t weapon_type = static_cast<uint32_t>(static_cast<const EventoSpawnArma&>(evento).weapon_type);
    serializar_weapon_type(bits, weapon_type, 32);
    return bits;
}

std::vector<uint8_t> Serializador::serializar_spawn_arma_box(const Evento& evento) {
    std::vector<uint8_t> bits(60); 

    uint8_t tipo_evento = static_cast<uint8_t>(evento.get_tipo());
    serializar_tipo_evento(bits, tipo_evento, 0);

    int x = static_cast<int>(static_cast<const EventoSpawnArmaBox&>(evento).x);
    int y = static_cast<int>(static_cast<const EventoSpawnArmaBox&>(evento).y);
    serializar_coordenadas(bits, x, y, 8, 20);

    uint32_t width_bits = static_cast<uint32_t>(static_cast<const EventoSpawnArmaBox&>(evento).width);
    serializar_tamaño_collidable(bits, width_bits, 32);
    uint32_t height_bits = static_cast<uint32_t>(static_cast<const EventoSpawnArmaBox&>(evento).height);
    serializar_tamaño_collidable(bits, height_bits, 44);

    uint32_t tipo_bits = static_cast<uint32_t>(static_cast<const EventoSpawnArmaBox&>(evento).weapon_type);
    serializar_weapon_type(bits, tipo_bits, 56);
    return bits;
}

std::vector<uint8_t> Serializador::serializar_spawn_proteccion_box(const Evento& evento) {
    std::vector<uint8_t> bits(33); 

    uint8_t tipo_evento = static_cast<uint8_t>(evento.get_tipo());
    serializar_tipo_evento(bits, tipo_evento, 0);

    int x = static_cast<int>(static_cast<const EventoSpawnProteccionBox&>(evento).x);
    int y = static_cast<int>(static_cast<const EventoSpawnProteccionBox&>(evento).y);
    serializar_coordenadas(bits, x, y, 8, 20);

    uint32_t tipo_bits = static_cast<uint32_t>(static_cast<const EventoSpawnProteccionBox&>(evento).proteccion_type);
    bits[32] = tipo_bits;

    return bits;
}




std::vector<uint8_t> Serializador::serializar_muerte(const Evento& evento) {
    std::vector<uint8_t> bits(24);

    uint8_t tipo_evento = static_cast<uint8_t>(evento.get_tipo());
    serializar_tipo_evento(bits, tipo_evento, 0);

    uint32_t id_bits = static_cast<uint32_t>(static_cast<const EventoMuerte&>(evento).id);
    serializar_id_dos(bits, id_bits, 8);

    return bits;
}

std::vector<uint8_t> Serializador::serializar_apuntar(const Evento& evento) {
    std::vector<uint8_t> bits(26);

    uint8_t tipo_evento = static_cast<uint8_t>(evento.get_tipo());
    serializar_tipo_evento(bits, tipo_evento, 0);

    uint32_t id_bits = static_cast<uint32_t>(static_cast<const EventoApuntar&>(evento).id);
    serializar_id_dos(bits, id_bits, 8);

    uint8_t direccion_bits = static_cast<uint8_t>(static_cast<const EventoApuntar&>(evento).direccion);
    
    std::bitset <2> bits_direccion(direccion_bits);
    for (int i = 0; i < 2; ++i) {
        bits[24 + i] = bits_direccion[i];
    }

    return bits;
}

std::vector<uint8_t> Serializador::serializar_agacharse(const Evento& evento) {
    std::vector<uint8_t> bits(24);

    serializar_tipo_evento(bits, static_cast<uint8_t>(evento.get_tipo()), 0);

    serializar_id_dos(bits, static_cast<const EventoAgacharse&>(evento).id, 8);

    return bits;
}

std::vector<uint8_t> Serializador::serializar_levantarse(const Evento& evento) {
    std::vector<uint8_t> bits(24);

    serializar_tipo_evento(bits, static_cast<uint8_t>(evento.get_tipo()), 0);

    serializar_id_dos(bits, static_cast<const EventoLevantarse&>(evento).id, 8);

    return bits;
}


std::vector<uint8_t> Serializador::serializar_win_round(const Evento& evento) {
    std::vector<uint8_t> bits(24);

    serializar_tipo_evento(bits, static_cast<uint8_t>(evento.get_tipo()), 0);

    serializar_id_dos(bits, static_cast<const EventoWinRound&>(evento).id, 8);

    return bits;
}

std::vector<uint8_t> Serializador::serializar_bala(const Evento& evento) {
    std::vector<uint8_t> bits(32);

    serializar_tipo_evento(bits, static_cast<uint8_t>(evento.get_tipo()), 0);

    int x = static_cast<int>(static_cast<const EventoBala&>(evento).x);
    int y = static_cast<int>(static_cast<const EventoBala&>(evento).y);
    serializar_coordenadas(bits, x, y, 8, 20);

    

    return bits;
}

std::vector<uint8_t> Serializador::serializar_caja_destruida(const Evento& evento) {
    std::vector<uint8_t> bits(32);

    serializar_tipo_evento(bits, static_cast<uint8_t>(evento.get_tipo()), 0);
    int x = static_cast<int>(static_cast<const EventoCajaDestruida&>(evento).x);
    int y = static_cast<int>(static_cast<const EventoCajaDestruida&>(evento).y);
    serializar_coordenadas(bits, x, y, 8, 20);


    return bits;
}



Evento::TipoEvento Serializador::deserializar_tipo_evento(const uint8_t* tipo_evento_data) {
    uint8_t tipo_evento_bits = 0;
    std::bitset<8> bits;
    for (int i = 0; i < 8; ++i) {
        bits[i] = tipo_evento_data[i];
    }
    tipo_evento_bits = static_cast<uint8_t>(bits.to_ulong());
    return static_cast<Evento::TipoEvento>(tipo_evento_bits);
}


std::unique_ptr<Evento> Serializador::deserializar_movimiento(const uint8_t* data) {
    int id = deserializar_id(data); 

    int x = deserializar_coordenadas(data + 16); 
    int y = deserializar_coordenadas(data + 28);

    ColorDuck color_asignado = deserializar_color(&data[40]);

    char is_flapping = static_cast<char>(data[44]); 

    char reset = static_cast<char>(data[45]);

    return std::make_unique<EventoMovimiento>(id, color_asignado, x, y, is_flapping, reset);
}



std::unique_ptr<Evento> Serializador::deserializar_pickup(const uint8_t* data) {
    int id = deserializar_id(data); 

    int x = deserializar_coordenadas(data + 16); 
    int y = deserializar_coordenadas(data + 28);

    WeaponType tipo = deserializar_tipo_weapon(&data[40]); 

    return std::make_unique<EventoPickup>(id, x, y, tipo);
}

std::unique_ptr<Evento> Serializador::deserializar_pickup_proteccion(const uint8_t* data) {
    int id = deserializar_id(data);

    int x = deserializar_coordenadas(data + 16);
    int y = deserializar_coordenadas(data + 28);

    ProteccionType tipo = static_cast<ProteccionType>(data[40]);

    return std::make_unique<EventoPickupProteccion>(id, x, y, tipo);
}



std::unique_ptr<Evento> Serializador::deserializar_spawn_arma(const uint8_t* data) {
    
    int x = deserializar_coordenadas(data);        
    int y = deserializar_coordenadas(data + 12);   
    WeaponType tipo = deserializar_tipo_weapon(&data[24]); 

    return std::make_unique<EventoSpawnArma>(x, y, tipo);
}

std::unique_ptr<Evento> Serializador::deserializar_spawn_arma_box(const uint8_t* data) {
    int x = deserializar_coordenadas(data);
    int y = deserializar_coordenadas(&data[12]);

    int width = deserializar_tamaño_collidable(data, 24);
    int height = deserializar_tamaño_collidable(data, 36);

    WeaponType tipo = deserializar_tipo_weapon(&data[48]);

    return std::make_unique<EventoSpawnArmaBox>(x, y, width, height, tipo);
}

std::unique_ptr<Evento> Serializador::deserializar_spawn_proteccion_box(const uint8_t* data) {
    
    int x = deserializar_coordenadas(data);
    int y = deserializar_coordenadas(data + 12);
    ProteccionType tipo = static_cast<ProteccionType>(data[24]);

    return std::make_unique<EventoSpawnProteccionBox>(x, y, tipo);
}


std::unique_ptr<Evento> Serializador::deserializar_muerte(const uint8_t* id_data) {
    int id = deserializar_id(id_data);

    return std::make_unique<EventoMuerte>(id);
}

std::unique_ptr<Evento> Serializador::deserializar_apuntar(const uint8_t* data) {
    int id = deserializar_id(data);

    uint32_t direccion_bits = 0;
    std::bitset<2> bits;
    for (int i = 0; i < 2; ++i) {
        bits[i] = data[16 + i];  
    }
    direccion_bits = static_cast<uint8_t>(bits.to_ulong());

    DireccionApuntada direccion = static_cast<DireccionApuntada>(direccion_bits);

    return std::make_unique<EventoApuntar>(id, direccion);
}

std::unique_ptr<Evento> Serializador::deserializar_bala(const uint8_t* data) {
    int x = deserializar_coordenadas(data);
    int y = deserializar_coordenadas(&data[12]); 

    return std::make_unique<EventoBala>(x, y);
}

std::unique_ptr<Evento> Serializador::deserializar_caja_destruida(const uint8_t* data) {
    int x = deserializar_coordenadas(data);
    int y = deserializar_coordenadas(&data[12]);
    
    return std::make_unique<EventoCajaDestruida>(x, y);
}

std::vector<uint8_t> Serializador::serializar_id(int id) {
    std::bitset <16> bits(id);
    std::vector<uint8_t> binary_bits(16);
    for (int i = 0; i < 16; ++i) {
        binary_bits[i] = bits[i];
    }

    return binary_bits;
}

int Serializador::deserializar_id(const uint8_t* id_binary) {
    std::bitset <16> bits;
    for (int i = 0; i < 16; ++i) {
        bits[i] = id_binary[i];
    }
    return static_cast<int>(bits.to_ulong());
}

void Serializador::imprimir_uint8_t_array(const uint8_t* array, size_t size) {
    for (size_t i = 0; i < size; ++i) {
        std::cout << static_cast<int>(array[i]);
    }
    std::cout<<std::endl;
}


int Serializador::deserializar_cantidad_collidables(const uint8_t* cantidad_data) {
    std::bitset<6> bits;
    for (int i = 0; i < 6; ++i) {
        bits[i] = cantidad_data[i];
    }
    return static_cast<int>(bits.to_ulong());
}

int Serializador::deserializar_cantidad(const uint8_t* cantidad_data) {
    uint32_t cantidad = 0;
    for (int i = 0; i < 32; ++i) {
        cantidad |= (cantidad_data[i] << (31 - i));
    }
    return static_cast<int>(cantidad);
}

std::vector<uint8_t> Serializador::serializar_mapa(const Evento& evento) {
    int cantidad = static_cast<const EventoMapa&>(evento).collidables.size();
    std::vector<uint8_t> bits(14 + cantidad * 52); 

    uint8_t tipo_evento = static_cast<uint8_t>(evento.get_tipo());
    serializar_tipo_evento(bits, tipo_evento, 0);
    serializar_cantidad(bits, cantidad, 8);

    const std::vector<Collidable*>& collidables = static_cast<const EventoMapa&>(evento).collidables;
    int offset = 14; 

    for (const auto& collidable : collidables) {
        uint32_t tipo_bits = static_cast<uint32_t>(collidable->getType());
        serializar_tipo_collidable(bits, tipo_bits, offset);

        int x_bits = static_cast<int>(collidable->position.x);
        int y_bits = static_cast<int>(collidable->position.y);

        serializar_coordenadas(bits, x_bits, y_bits, offset + 4, offset + 16);

        int width_bits = static_cast<int>(collidable->width);
        serializar_tamaño_collidable(bits, width_bits, offset + 28);

        int height_bits = static_cast<int>(collidable->height);
        serializar_tamaño_collidable(bits, height_bits, offset + 40);



        offset += 52; 
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

    CollidableType tipo = static_cast<CollidableType>(deserializar_tipo_collidable(collidable_data));

    int x = deserializar_coordenadas(&collidable_data[4]);
    int y = deserializar_coordenadas(&collidable_data[16]);

    int width = deserializar_tamaño_collidable(collidable_data, 28);
    int height = deserializar_tamaño_collidable(collidable_data, 40);

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


void Serializador::serializar_tipo_evento(std::vector<uint8_t>& bits, uint8_t tipo_evento, size_t offset) {
    std::bitset<8> tipo_bits(tipo_evento);
    for (int i = 0; i < 8; ++i) {
        bits[offset + i] = tipo_bits[i];
    }
}


void Serializador::serializar_coordenadas(std::vector<uint8_t>& bits, int x, int y, int offset_x, int offset_y) {
    std::bitset<12> x_bits(x);
    for (int i = 0; i < 12; ++i) {
        bits[offset_x + i] = x_bits[i];
    }

    std::bitset<12> y_bits(y);
    for (int i = 0; i < 12; ++i) {
        bits[offset_y + i] = y_bits[i];
    }
}

void Serializador::serializar_color(std::vector<uint8_t>& bits, uint8_t color, int offset) {
    std::bitset<4> color_bits(color);
    for (int i = 0; i < 4; ++i) {
        bits[offset + i] = color_bits[i];
    }
}

void Serializador::serializar_id_dos(std::vector<uint8_t>& bits, uint32_t id, size_t offset) {
    std::bitset<16> id_bits(id);
    for (int i = 0; i < 16; ++i) {
        bits[offset + i] = id_bits[i];
    }
}

void Serializador::serializar_tamaño_collidable(std::vector<uint8_t>& bits, uint32_t size, size_t offset) {
    std::bitset<12> size_bits(size);
    for (int i = 0; i < 12; ++i) {
        bits[offset + i] = size_bits[i];
    }
    
}

void Serializador::serializar_tipo_collidable(std::vector<uint8_t>& bits, uint32_t tipo, size_t offset) {
    std::bitset<4> tipo_bits(tipo);
    for (int i = 0; i < 4; ++i) {
        bits[offset + i] = tipo_bits[i];
    }
}

void Serializador::serializar_weapon_type(std::vector<uint8_t>& bits, uint8_t weapon_type, size_t offset) {
    std::bitset<4> type_bits(weapon_type);
    for (int i = 0; i < 4; ++i) {
        bits[offset + i] = type_bits[i];
    }
}

void Serializador::serializar_cantidad(std::vector<uint8_t>& bits, int cantidad, size_t offset) {
    std::bitset<12> cantidad_bits(cantidad);
    for (int i = 0; i < 12; ++i) {
        bits[offset + i] = cantidad_bits[i];
    }

}

int Serializador::deserializar_coordenadas(const uint8_t* data) {
    std::bitset <12> bits;
    for (int i = 0; i < 12; ++i) {
        bits[i] = data[i];
    }
    return static_cast<int>(bits.to_ulong());
}

ColorDuck Serializador::deserializar_color(const uint8_t* data) {
    std::bitset<4> bits;
    for (int i = 0; i < 4; ++i) {
        bits[i] = data[i];
    }
    uint8_t color_bits = static_cast<uint8_t>(bits.to_ulong());
    return static_cast<ColorDuck>(color_bits);
}


WeaponType Serializador::deserializar_tipo_weapon(const uint8_t* weapon_type_data) {
    std::bitset<4> bits;
    for (int i = 0; i < 4; ++i) {
        bits[i] = weapon_type_data[i];
    }
    uint8_t tipo_bits = static_cast<uint8_t>(bits.to_ulong());
    return static_cast<WeaponType>(tipo_bits);
}


int Serializador::deserializar_tamaño_collidable(const uint8_t* data, int offset) {
    std::bitset<12> dimension_bits;
    for (int i = 0; i < 12; ++i) {
        dimension_bits[i] = data[offset + i];
    }
    return static_cast<int>(dimension_bits.to_ulong());
}

CollidableType Serializador::deserializar_tipo_collidable(const uint8_t* collidable_data) {
    std::bitset<4> bits;
    for (int i = 0; i < 4; ++i) {
        bits[i] = collidable_data[i];
    }
    uint8_t tipo_bits = static_cast<uint8_t>(bits.to_ulong());
    return static_cast<CollidableType>(tipo_bits);
}

