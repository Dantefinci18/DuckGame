#ifndef COMMON_SERIALIZADOR_H
#define COMMON_SERIALIZADOR_H

#include <string>
#include <vector>
#include <cstdint>
#include <memory>
#include <bitset>
#include <tuple>
#include "../common/common_accion.h"
#include "../common/common_evento.h"
#include "../server/Collidable.h"
#include "../server/Platform.h"
#include "../server/Player.h"
#include "../server/SpawnPlace.h"
#include "../server/Box.h"
#include "../server/server_leaderboard.h"

class Serializador {
private:
    std::vector<uint8_t> serializar_enum(std::bitset<5> bits);
    uint8_t deserializar_enum(const uint8_t* data);

public:

    std::vector<uint8_t> serializar_accion(ComandoAccion &accion);

    ComandoAccion deserializar_accion(const uint8_t* data);

    std::vector<uint8_t> serializar_evento(const Evento& evento);
    std::vector<uint8_t> serializar_pickup(const Evento& evento);
    std::vector<uint8_t> serializar_pickup_proteccion(const Evento& evento);
    std::vector<uint8_t> serializar_spawn_arma(const Evento& evento);
    std::vector<uint8_t> serializar_spawn_arma_box(const Evento& evento);
    std::vector<uint8_t> serializar_spawn_proteccion_box(const Evento& evento);
    std::vector<uint8_t> serializar_movimiento(const Evento& evento);
    std::vector<uint8_t> serializar_muerte(const Evento& evento);
    std::vector<uint8_t> serializar_apuntar(const Evento& evento);
    std::vector<uint8_t> serializar_espera(const Evento::TipoEvento& evento);
    std::vector<uint8_t> serializar_agacharse(const Evento& evento);
    std::vector<uint8_t> serializar_levantarse(const Evento& evento);
    std::vector<uint8_t> serializar_win_round(const Evento& evento);
    std::vector<uint8_t> serializar_bala(const Evento& evento);
    std::vector<uint8_t> serializar_caja_destruida(const Evento& evento);


    std::unique_ptr<Evento> deserializar_movimiento(const uint8_t* data);
    std::unique_ptr<Evento> deserializar_pickup(const uint8_t* data);
    std::unique_ptr<Evento> deserializar_pickup_proteccion(const uint8_t* id_data, const uint8_t* x_data, const uint8_t* y_data, const uint8_t* proteccion_type_data);
    std::unique_ptr<Evento> deserializar_spawn_arma(const uint8_t* data);
    std::unique_ptr<Evento> deserializar_spawn_arma_box(const uint8_t* data);
    std::unique_ptr<Evento> deserializar_spawn_proteccion_box(const uint8_t* x_data, const uint8_t* y_data, const uint8_t* proteccion_type_data);
    std::unique_ptr<Evento> deserializar_muerte(const uint8_t* id_data);
    std::unique_ptr<Evento> deserializar_apuntar(const uint8_t* data);
    std::unique_ptr<Evento> deserializar_caja_destruida(const uint8_t* data);
    std::unique_ptr<Evento> deserializar_bala(const uint8_t* data);
    Evento::TipoEvento deserializar_tipo_evento(const uint8_t* tipo_evento_data);

    std::vector<uint8_t> serializar_id(int id);
    
    int deserializar_id(const uint8_t* id_binary);

    void imprimir_uint8_t_array(const uint8_t* array, size_t size);

    int deserializar_cantidad_collidables(const uint8_t* cantidad_data);

    int deserializar_cantidad(const uint8_t* cantidad_data);

    std::vector<uint8_t> serializar_mapa(const Evento& evento);

    
    Collidable* deserializar_collidable(const uint8_t* collidable_data);
    std::tuple<int, int> deserializar_tuple64(const uint8_t* tuple_data);

    void serializar_tipo_evento(std::vector<uint8_t>& bits, uint8_t tipo_evento, size_t offset);
    void serializar_coordenadas(std::vector<uint8_t>& bits, int x, int y, int offset_x, int offset_y);
    void serializar_color(std::vector<uint8_t>& bits, uint8_t color, int offset);
    void serializar_id_dos(std::vector<uint8_t>& bits, uint32_t id, size_t offset);
    void serializar_tamaño_collidable(std::vector<uint8_t>& bits, uint32_t size, size_t offset);
    void serializar_tipo_collidable(std::vector<uint8_t>& bits, uint32_t tipo, size_t offset);
    void serializar_weapon_type(std::vector<uint8_t>& bits, uint8_t weapon_type, size_t offset);
    void serializar_cantidad(std::vector<uint8_t>& bits, int cantidad, size_t offset);


    int deserializar_coordenadas(const uint8_t* data);
    ColorDuck deserializar_color(const uint8_t* data);
    WeaponType deserializar_tipo_weapon(const uint8_t* weapon_type_data);
    int deserializar_tamaño_collidable(const uint8_t* data, int offset);
    CollidableType deserializar_tipo_collidable(const uint8_t* collidable_data);
};
#endif //COMMON_SERIALIZADOR_H