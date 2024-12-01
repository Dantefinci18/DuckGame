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
    std::vector<uint8_t> serializar_enum(std::bitset<8> bits);
    uint8_t deserializar_enum(const uint8_t* data);

public:

    std::vector<uint8_t> serializar_accion(ComandoAccion &accion);

    ComandoAccion deserializar_accion(const uint8_t* data);

    std::vector<uint8_t> serializar_evento(const Evento& evento);
    std::vector<uint8_t> serializar_pickup(const Evento& evento);
    std::vector<uint8_t> serializar_spawn_arma(const Evento& evento);
    std::vector<uint8_t> serializar_spawn_arma_box(const Evento& evento);
    std::vector<uint8_t> serializar_movimiento(const Evento& evento);
    std::vector<uint8_t> serializar_muerte(const Evento& evento);
    std::vector<uint8_t> serializar_apuntar(const Evento& evento);
    std::vector<uint8_t> serializar_espera(const Evento::TipoEvento& evento);
    std::vector<uint8_t> serializar_agacharse(const Evento& evento);
    std::vector<uint8_t> serializar_levantarse(const Evento& evento);
    std::vector<uint8_t> serializar_win_round(const Evento& evento);
    std::vector<uint8_t> serializar_bala(const Evento& evento);
    std::vector<uint8_t> serializar_caja_destruida(const Evento& evento);


    std::unique_ptr<Evento> deserializar_movimiento(const uint8_t* id_data,const uint8_t* ,const uint8_t* x_data, const uint8_t* y_data, char is_flapping, char reset);
    std::unique_ptr<Evento> deserializar_pickup(const uint8_t* id_data, const uint8_t* x_data, const uint8_t* y_data, const uint8_t* weapon_type_data);
    std::unique_ptr<Evento> deserializar_spawn_arma(const uint8_t* x_data, const uint8_t* y_data, const uint8_t* weapon_type_data);
    std::unique_ptr<Evento> deserializar_spawn_arma_box(const uint8_t* x_data, const uint8_t* y_data, 
    const uint8_t* width_data, const uint8_t* height_data, const uint8_t* weapon_type_data);
    std::unique_ptr<Evento> deserializar_muerte(const uint8_t* id_data);
    std::unique_ptr<Evento> deserializar_apuntar(const uint8_t* id_data, const uint8_t* direccion_data);
    std::unique_ptr<Evento> deserializar_caja_destruida(const uint8_t* x_data, const uint8_t* y_data);
    std::unique_ptr<Evento> deserializar_bala(const uint8_t* x_data, const uint8_t* y_data);
    Evento::TipoEvento deserializar_tipo_evento(const uint8_t* tipo_evento_data);

    std::vector<uint8_t> serializar_id(int id);
    
    int deserializar_id(const uint8_t* id_binary);

    void imprimir_uint8_t_array(const uint8_t* array, size_t size);

    int deserializar_cantidad(const uint8_t* cantidad_data);

    std::vector<uint8_t> serializar_mapa(const Evento& evento);

    
    Collidable* deserializar_collidable(const uint8_t* collidable_data);
    std::tuple<int, int> deserializar_tuple64(const uint8_t* tuple_data);

    void serializar_tipo_evento(std::vector<uint8_t>& bits, uint8_t tipo_evento, size_t offset);

    void serializar_coordenadas(std::vector<uint8_t>& bits, int x, int y, int offset_x, int offset_y);

    void serializar_color(std::vector<uint8_t>& bits, uint8_t color, int offset);

    void serializar_id_dos(std::vector<uint8_t>& bits, uint32_t id, size_t offset);

};
#endif //COMMON_SERIALIZADOR_H