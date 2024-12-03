#ifndef COMMON_SERIALIZADOR_H
#define COMMON_SERIALIZADOR_H

#include <string>
#include <vector>
#include <cstdint>
#include <memory>
#include <bitset>
#include <tuple>
#include <list>
#include "common_accion.h"
#include "common_evento.h"
#include "../server/Collidable.h"
#include "../server/Platform.h"
#include "../server/Player.h"
#include "../server/SpawnPlace.h"
#include "../server/Box.h"
#include "../server/server_leaderboard.h"
#include "common_partida.h"

class Serializador {

public:
    void serializar_enum(uint8_t tipo, std::vector<uint8_t>& buffer);
    void serializar_numero_entero(int numero, std::vector<uint8_t>& buffer,int j);
    void serializar_string(const std::string& string,std::vector<uint8_t>& buffer,int j);
    uint8_t deserializar_enum(const uint8_t* data);
    int deserializar_numero_entero(const uint8_t* data);
    std::string deserializar_string(const uint8_t *data, size_t tamanio);
    
    std::vector<uint8_t> serializar_accion(std::shared_ptr<Accion> accion);
    ComandoAccion deserializar_tipo_accion(const uint8_t* data);
    
    std::shared_ptr<AccionNuevaPartida> deserializar_nueva_partida(
        const uint8_t* data_nombre, size_t, const uint8_t* data_jugadores, const uint8_t* mapa);
    
    std::vector<uint8_t> serializar_partidas(std::list<Partida> partidas);

    std::vector<uint8_t> serializar_evento(const Evento& evento);
    std::vector<uint8_t> serializar_pickup(const Evento& evento);
    std::vector<uint8_t> serializar_pickup_proteccion(const Evento& evento);
    std::vector<uint8_t> serializar_spawn_arma(const Evento& evento);
    std::vector<uint8_t> serializar_spawn_arma_box(const Evento& evento);
    std::vector<uint8_t> serializar_spawn_proteccion_box(const Evento& evento);
    std::vector<uint8_t> serializar_movimiento(const Evento& evento);
    std::vector<uint8_t> serializar_disparo(const Evento& evento);
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
    std::unique_ptr<Evento> deserializar_pickup_proteccion(const uint8_t* id_data, const uint8_t* x_data, const uint8_t* y_data, const uint8_t* proteccion_type_data);
    std::unique_ptr<Evento> deserializar_spawn_arma(const uint8_t* x_data, const uint8_t* y_data, const uint8_t* weapon_type_data);
    std::unique_ptr<Evento> deserializar_spawn_arma_box(const uint8_t* x_data, const uint8_t* y_data, 
        const uint8_t* width_data, const uint8_t* height_data, const uint8_t* weapon_type_data);
    std::unique_ptr<Evento> deserializar_spawn_proteccion_box(const uint8_t* x_data, const uint8_t* y_data, const uint8_t* proteccion_type_data);
    std::unique_ptr<Evento> deserializar_disparo(const uint8_t* id_data);
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

};
#endif //COMMON_SERIALIZADOR_H